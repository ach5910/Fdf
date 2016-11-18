/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 04:09:01 by ahunt             #+#    #+#             */
/*   Updated: 2016/11/10 04:09:04 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>

void *win;
void *mlx;

int *points;
// char **points;
int color = 0x00FFFFFF;
int len;
int max_strs;
int w = 10;
int pad = 150;
int key_len = 0;
char *file;
char *arw_file;
unsigned char *keys;
double per = 1;
const unsigned char tran_h = 0x01;
const unsigned char tran_v = 0x02;
const unsigned char scl = 0x04;
const unsigned char rot_x = 0x08;
const unsigned char rot_y = 0x10;
const unsigned char rot_z = 0x20;
const unsigned char mous = 0x40;
const unsigned char sign = 0x80;
unsigned char flags = 0;

typedef struct s_vec
{
	double	x;
	double y;
	double	z;
	int color;
}				t_vec;
t_vec *pnts;
t_vec *up;
t_vec *down;
t_vec *left;
t_vec *right;

void get_map(void);
void draw_map(void);
void rotation_x(double dir);
void rotation_y(double dir);
void rotation_z(double dir);
void clear(void);
void perspective(double dir);
void scale(double factor);
void translation_h(double shift);
void translation_v(double shift);
void draw_tri(void);

int colors[24] = {0};

void init_colors()
{
	colors[0] = 0x00FFFFFF;
	colors[1] = 0x8b0000; //midnight blue
	colors[2] = 0xff0000; //sky blue
	colors[3] = 0xff69b4; //cyan
	colors[4] = 0xff6347; //dark torquoise
	colors[5] = 0xff4500; //dark green
	colors[6] = 0xffd700; // green
	colors[7] = 0x32cd32; //lime green
	colors[8] = 0x9acd32; //yellow
	colors[9] = 0xff00; //orange
	colors[10] = 0x2e8b57; //red
	colors[11] = 0x6400; //lavender
	colors[12] = 0xced1; //chocolate
	colors[13] = 0xffff; //violet
	colors[15] = 0x87ceeb; //hotpink
	colors[17] = 0x63b8ff; //violet
	colors[20] = 0x191970; //purple
	colors[21] = 0xa020f0;
	colors[22] = 0x8b008b;
	colors[23] = 0xee82ee;
}
// "darkred" , 0x8b0000
// "red" , 0xff0000
// "hotpink" , 0xff69b4
// "tomato1" , 0xff6347
// "orangered1" , 0xff4500
// "orange" , 0xffa500
// "gold" , 0xffd700
// "yellow" , 0xffff00
// "lime green" , 0x32cd32
// "yellow green" , 0x9acd32
// "green" , 0xff00
//"sea green" , 0x2e8b57
// "dark green" , 0x6400
// "dark turquoise" , 0xced1
// "cyan" , 0xffff
// "sky blue" , 0x87ceeb
// "steelblue1" , 0x63b8ff
// "midnight blue" , 0x191970
// "purple" , 0xa020f0
//"dark magenta" , 0x8b008b
// "violet" , 0xee82ee
//"violetred1" , 0xff3e96


// "lavender" , 0xe6e6fa
// "dim gray" , 0x696969


// "tan" , 0xd2b48c
// "chocolate" , 0xd2691e

void draw(int color_ch)
{
	int x;
	int y;

	color += color_ch;
	y = 50;
	while (y <= 550)
	{
		x = 50;
		while (x <= 750)
		{

			if (x % 50 == 0 || y % 50 == 0)
				mlx_pixel_put(mlx, win, x, y, color);
			x++;
		}
		y++;
	}
}

// void apply_trans(void)
// {
// 	double temp;

// 	temp = tran_v;
// 	translation_v(tran_v);
// 	tran_v = temp;

// 	temp = tran_h;
// 	translation_h(tran_h);
// 	tran_h = temp;

// 	temp = rot_x;
// 	if (rot_x)
// 		rotation_x(rot_x);
// 	rot_x = temp;

// 	temp = rot_y;
// 	if (rot_y)
// 		rotation_y(rot_y);
// 	rot_y = temp;

// 	temp = rot_z;
// 	if (rot_z)
// 		rotation_z(rot_z);
// 	rot_z = temp;

// 	temp = scl;
// 	scale(scl);
// 	scl = temp;

// 	draw_map();
// }
int my_key_recall(unsigned char keycode, void *mlx)
{
	printf("key event %d\n", keycode);
	if (keycode & sign)
	{
		if (keycode & rot_x)
			rotation_x(-0.125);
		else if (keycode & rot_y)
			rotation_y(-0.125);
		else if (keycode & rot_z)
			rotation_z(-0.125);
		else if (keycode & scl)
			scale(0.8);
		else if (keycode & tran_h)
			translation_h(-10.0);
		else if (keycode & tran_v)
			translation_v(-10.0);
	}
	else
	{
		if (keycode & rot_x)
			rotation_x(0.125);
		else if (keycode & rot_y)
			rotation_y(0.125);
		else if (keycode & rot_z)
			rotation_z(0.125);
		else if (keycode & scl)
			scale(1.25);
		else if (keycode & tran_h)
			translation_h(10.0);
		else if (keycode & tran_v)
			translation_v(10.0);
	}
	// else if (keycode == 53)
	// 	exit(1);
	// else if (keycode == 15)
	// {
	// 	mlx_clear_window();
	// 	get_map();
	// }
	return (0);
}

int my_key_funct(int kc, void *mlx)
{
	printf("key event %d\n", kc);
	// if (kc == 0 || kc == 1 || kc == 2 || kc == 3 || kc == 6 || kc == 7 ||
	// 	kc == 24|| kc == 27 || (kc >= 123 && kc <= 126))
	if (flags && !(flags & mous))
		flags = 0;
	// if (keycode == 0)
	// 	rotation_x(0.25);
	// else if (keycode == 1)
	// 	rotation_x(-0.25);
	// else if (keycode == 2)
	// 	rotation_y(0.25);
	// else if (keycode == 3)
	// 	rotation_y(-0.25);
	// else if (keycode == 6)
	// 	rotation_z(0.25);
	// else if (keycode == 7)
	// 	rotation_z(-0.25);
	// if (keycode == 0 || keycode == 1)
	// 	rot_x = 0;
	// else if (keycode == 2 || keycode == 3) 
	// 	rot_y = 0;
	// else if (keycode == 6 || keycode == 7)
	// 	rot_z = 0;
	else if (kc == 75)
		perspective(0.5);
	else if (kc == 67)
		perspective(2);
	else if (kc == 78)
		perspective(-1);
	// else if (keycode == 24)
	// 	scale(2);
	// else if (keycode == 27)
	// 	scale(0.5);
	// else if (keycode == 123)
	// 	translation_h(100.0);
	// else if (keycode == 124)
	// 	translation_h(-100.0);
	// else if (keycode == 125)
	// 	translation_v(-100.0);
	// else if (keycode == 126)
	// 	translation_v(100.0);
	else if (kc == 53)
		exit(1);
	else if (kc == 15)
	{
		ft_bzero((void *)keys, 100);
		key_len = 0;
		get_map();
		mlx_clear_window(mlx, win);
		draw_map();
	}
	return (0);
}

void translation_h(double shift)
{
	int i;

	i = 0;
	while (i < len * max_strs)
	{
		pnts[i].x += shift;
		i++;
	}
	// clear();
	// draw_map();
}

void translation_v(double shift)
{
	int i;

	i = 0;
	while (i < len * max_strs)
	{
		pnts[i].y += shift;
		i++;
	}
	// clear();
	// draw_map();
}

void scale(double factor)
{
	int i;

	//scl *= factor;
	i = 0;
	double center_x = 600;
	double center_y = 400;
	while (i < len * max_strs)
	{
		pnts[i].x = center_x + factor * (pnts[i].x - center_x);
		pnts[i].y = center_y + factor * (pnts[i].y - center_y);
		pnts[i].z *= factor;
		i++;
	}
	// clear();
	// draw_map();
}
void	perspective(double dir)
{
	int i;
	int end;

	per *= dir;
	// double temp_z;

	mlx_clear_window(mlx, win);
	get_map();
	// translation_h(600 - (len / 2));
	// translation_v(400 - (max_strs / 2));
	// scale(w);
	i = 0;
	while (i < len * max_strs)
	{
		//if (pnts[i].color != 0x00FFFFFF)
		pnts[i].z = per * pnts[i].z;
		// temp_z = pnts[i].z == 0 ? 1 : pnts[i].z;
		// pnts[i].x = 0.5 * pnts[i].x / temp_z;
		// pnts[i].y = 0.5 * pnts[i].y / temp_z;
		i++;
	}
	// scale(w);
	// translation_v(pad);
	// translation_h(pad);

	i = 0;
	while (i < key_len)
	{
		ft_printf("\nKey = %d", (int)keys[i]);
		my_key_recall((int)keys[i], mlx);
		i++;
	}
	//apply_trans();
	//ft_bzero((void *)keys, ft_strlen(keys));
	draw_map();
	
	
}

double mean_x()
{
	int i;
	double sum;

	sum = 0;
	i = 0;
	while (i < len * max_strs)
	{
		sum += pnts[i].x;
		i++;
	}
	return (sum / (len * max_strs));
}

double mean_y()
{
	int i;
	double sum;

	sum = 0;
	i = 0;
	while (i < len * max_strs)
	{
		sum += pnts[i].y;
		i++;
	}
	return (sum / (len * max_strs));
}

double mean_z()
{
	int i;
	double sum;

	sum = 0;
	i = 0;
	while (i < len * max_strs)
	{
		sum += pnts[i].z;
		i++;
	}
	return (sum / (len * max_strs));
}

void	rotation_y(double dir)
{

	int i;
	double tmp_x;
	double c_x = mean_x();
	double c_z = mean_z();
	double d;
	double x;
	double z;
	double theta;

	i = 0;
	while (i < len * max_strs)
	{
		x = pnts[i].x - c_x;
		z = pnts[i].z - c_z;
		d = hypot(x, z);
		theta = atan2(x, z) + dir;
		pnts[i].z = c_z + d * cos(theta);
		pnts[i].x = c_x + d * sin(theta);
		i++;
	}

	// int i;
	// double tmp_x;

	// rot_y += dir;
	// i = 0;
	// printf("rot_y dir = %f", dir);
	// while (i < len * max_strs)
	// {
	// 	tmp_x = pnts[i].x * cos(dir * M_PI / 16) + pnts[i].z * (dir) * sin(M_PI / 16);
	// 	pnts[i].z = pnts[i].x * (-dir) * sin( M_PI / 16) + pnts[i].z * cos(dir * M_PI / 16);
	// 	pnts[i].x = tmp_x;
	// 	i++;
	// }
	// clear();
	// draw_map();
}

void	rotation_z(double dir)
{
	int i;
	double tmp_x;
	double c_x = mean_x();
	double c_y = mean_y();
	double d;
	double x;
	double y;
	double theta;

	i = 0;
	while (i < len * max_strs)
	{
		x = pnts[i].x - c_x;
		y = pnts[i].y - c_y;
		d = hypot(y, x);
		theta = atan2(y, x) + dir;
		pnts[i].x = c_x + d * cos(theta);
		pnts[i].y = c_y + d * sin(theta);
		i++;
	}

	// int i;
	// double tmp_x;

	// rot_z += dir;
	// i = 0;
	// while (i < len * max_strs)
	// {
	// 	tmp_x = pnts[i].x * cos(dir * M_PI / 16) + pnts[i].y * (-dir) * sin(M_PI / 16 );
	// 	pnts[i].y = pnts[i].x * (dir) * sin(M_PI / 16 ) + pnts[i].y * cos(dir * M_PI / 16 );
	// 	pnts[i].x = tmp_x;
	// 	i++;
	// }
	// clear();
	// draw_map();
}

void	rotation_x(double dir)
{
	int i;
	double tmp_y;
	double c_z = mean_z();
	double c_y = mean_y();
	double d;
	double z;
	double y;
	double theta;

	i = 0;
	while (i < len * max_strs)
	{
		z = pnts[i].z - c_z;
		y = pnts[i].y - c_y;
		d = hypot(y, z);
		theta = atan2(y, z) + dir;
		pnts[i].z = c_z + d * cos(theta);
		pnts[i].y = c_y + d * sin(theta);
		i++;
	}

	// int i;
	// double tmp_y;

	// rot_x += dir;
	// i = 0;
	// while (i < len * max_strs)
	// {
	// 	tmp_y = pnts[i].y * cos(dir * M_PI / 16) + pnts[i].z * (-dir) * sin(M_PI / 16);
	// 	pnts[i].z = pnts[i].y * (dir) * sin(M_PI / 16) + pnts[i].z * cos(dir * M_PI / 16);
	// 	pnts[i].y = tmp_y;
	// 	i++;
	// }
	// clear();
	// draw_map();
}

void clear(void)
{
	int i;
	int j;

	j = 0;
	while (j <= 800)
	{
		i = 0;
		while (i <= 1200)
		{
			mlx_pixel_put(mlx, win, i, j, 0x000000);
			i++;
		}
		j++;
	}
}

void draw_lines_x(int index, int inc)
{
	double dx = fabs(pnts[index + inc].x - pnts[index].x);
	double dy = fabs(pnts[index + inc].y - pnts[index].y);
	double p = (2 * dy) - dx;
	double i;
	double j;
	double j_incr;
	int ci;
	int cf;
	int end;
	int start;

	end = pnts[index + inc].x > pnts[index].x ? index + inc : index;
	start = pnts[index + inc].x > pnts[index].x ? index : index + inc;
	i = pnts[start].x;
	j = pnts[start].y;
	j_incr = pnts[end].y > pnts[start].y ? 1 : -1;
	ci = pnts[start].color;
	cf = pnts[end].color;
	//color = pnts[index].color == pnts[index + 1].color ? pnts[index].color : 0x00FFFFFF;

	// if (pnts[index].z == 0)
	// 	ci = 0x00FFFFFF;s
	// else
	// 	ci = 0x8b0000;
	// if (pnts[index + 1].z == 0)
	// 	cf = 0x00FFFFFF;
	// else
	// 	cf = 0x8b0000;
	while (i < pnts[end].x)
	{
		color = ci + (cf - ci) * (i - pnts[start].x) / dx;
		mlx_pixel_put(mlx, win, (i), (j), color);
		// mlx_pixel_put(mlx, win, i, j, color);
		if (p < 0)
		{
			p += (2 * dy);
		}
		else
		{
			p += (2 * dy) - (2 * dx);
			j += j_incr;
		}
		i++;
	}
}

void draw_lines_y(int index, int inc)
{
	double dx = fabs(pnts[index + inc].x - pnts[index].x);
	double dy = fabs(pnts[index + inc].y - pnts[index].y);
	double p = (2 * dx) - dy;
	double i;
	double j;
	int ci;
	int cf;
	int end;
	int start;
	double j_incr;

	// end = pnts[index + inc].y > pnts[index].y ? pnts[index + inc].y : pnts[index].y;
	// i = pnts[index + inc].y > pnts[index].y ? pnts[index].y : pnts[index + inc].y;
	// j_incr = pnts[index + inc].x > pnts[index].x ? 1 : -1;

	end = pnts[index + inc].y > pnts[index].y ? index + inc : index;
	start = pnts[index + inc].y > pnts[index].y ? index : index + inc;
	i = pnts[start].y;
	j = pnts[start].x;
	j_incr = pnts[end].x > pnts[start].x ? 1 : -1;
	ci = pnts[start].color;
	cf = pnts[end].color;

	
	mlx_pixel_put(mlx, win, (j) , (i) , pnts[index].color);
	i++;

	//color = pnts[index].color == pnts[index + s].color ? pnts[index].color : 0x00FFFFFF;
	// if (pnts[index].z == pnts[index + len].z && pnts[index].z != 0)
	// {
	// 	// if (pnts[index].z == 1)
	// 	// 	color = 0x191970;
	// 	// if (pnts[index].z == 2)
	// 	// 	color = 0x87ceeb;
	// 	// if (pnts[index].z == 3)
	// 	// 	color = 0x32cd32;
	// 	// if (pnts[index].z == 5)
	// 	// 	color = 0x228b22;
	// 	// if (pnts[index].z == 7)
	// 	// 	color = 0xffff00;
	// 	// if (pnts[index].z == 10)
	// 		color = 0x8b0000;
	// 	// if (pnts[index].z == 15)
	// 	// 	color = 0xd2b48c;
	// 	// if (pnts[index].z == 20)
	// 	// 	color = 0xffa500;
	// }
	// else
	// 	color = 0x00FFFFFF;

	// if (pnts[index].z == 0)
	// 	ci = 0x00FFFFFF;
	// else
	// 	ci = 0x8b0000;
	// if (pnts[index + len].z ==./0)
	// 	cf = 0x00FFFFFF;
	// else
	// 	cf = 0x8b0000;
	while (i < pnts[end].y)
	{
		color = ci + (cf - ci) * (i - pnts[start].y) / dy;
		mlx_pixel_put(mlx, win, (j), (i), color);
		// mlx_pixel_put(mlx, win, i, j, color);
		if (p < 0)
		{
			p += (2 * dx);
		}
		else
		{
			p += (2 * dx) - (2 * dy);
			j += j_incr;
		}
		i++;
	}
}

// double amean_x()
// {
// 	int i;
// 	double sum;

// 	sum = 0;
// 	i = 0;
// 	while (i < len * max_strs)
// 	{
// 		sum += up[i].x;
// 		i++;
// 	}
// 	return (sum / (len * max_strs));
// }

// double amean_y()
// {
// 	int i;
// 	double sum;

// 	sum = 0;
// 	i = 0;
// 	while (i < len * max_strs)
// 	{
// 		sum += up[i].y;
// 		i++;
// 	}
// 	return (sum / (len * max_strs));
// }

// void rot_arrow(t_vec *arw, double dir, double x1, double y1)
// {
// 	int i;
// 	double tmp_x;
// 	double c_x = amean_x();
// 	double c_y = amean_y();
// 	double d;
// 	double x;
// 	double y;
// 	double theta;

// 	i = 0;
// 	while (i < 2500)
// 	{
// 		x = arw[i].x - c_x;
// 		y = arw[i].y - c_y;
// 		d = hypot(y, x);
// 		theta = atan2(y, x) + dir;
// 		arw[i].x = c_x + d * cos(theta);
// 		arw[i].y = c_y + d * sin(theta);
// 		mlx_pixel_put(mlx, win, arw[i].x + x1, arw[i].y + y1, arw[i].color);
		
// 		i++;
// 	}
// }

void draw_tri(void)
{
	int i;
	int j;
	int c;

	j  = 0;
	while (j < 80)
	{
		i = 0;
		while (i < 80)
		{
			c = 0x00FFFFFF;
			if ( j - i >= -40 && j + i >= 40 && j <= 40)
				mlx_pixel_put(mlx, win, i + 1050, j + 590, c);
			if (j + i <= 80 && j >= i)
				mlx_pixel_put(mlx, win, i + 1150, j + 650, c);
			if (j + i <= 80 && j <= i)
				mlx_pixel_put(mlx, win, i + 1050, j + 750, c);
			if (j + i >= 40 && j - i <= 40 && i <= 40)
				mlx_pixel_put(mlx, win, i + 990, j + 650, c);
			i++;
		}
		j++;
	}
}
// void put_arrow(t_vec *arw, double x, double y)
// {
// 	double i;
// 	double j;
// 	int p;

// 	p = 0;
// 	j = 0;
// 	while (j < 25)
// 	{
// 		i = 0;
// 		while (i < 50)
// 		{
// 			mlx_pixel_put(mlx, win, i + x, j + y, arw[p].color);
// 			//printf("X = %f Y = %f Z = %f C = %d\t", arw[p].x, arw[p].y, arw[p].z, arw[p].color);
// 			p++;
// 			i++;
// 		}
// 		j++;
// 	}
	
// }
void draw_legend(void)
{
	draw_tri();
	mlx_string_put(mlx, win, 30, 25, 16777215, "***TRANSFORMATION COMMANDS***");
	mlx_string_put(mlx, win, 30, 50, 16777215, "Exit  		: 'ESC'");
	mlx_string_put(mlx, win, 30, 70, 16777215, "Reset 		: 'r'");
	mlx_string_put(mlx, win, 30, 90, 16777215, "Scale 		: '-'  '+' (Keypad)");
	mlx_string_put(mlx, win, 30, 110, 16777215, "Depth 		: '*'  '/'  '-' (Numpad)");
	mlx_string_put(mlx, win, 30, 130, 16777215,"Translation : 'Arrows'");
	mlx_string_put(mlx, win, 30, 150, 16777215,"Rotation 	:");
	mlx_string_put(mlx, win, 30, 170, 16777215,"     x - 'd'  'f'");
	mlx_string_put(mlx, win, 30, 190, 16777215,"     y - 'a'  's'");
	mlx_string_put(mlx, win, 30, 210, 16777215,"     z - 'z'  'x'");
	
	

	
}

// void draw_arrows(void)
// {
// 	rot_arrow(up, 0, 1065, 585);
// 	rot_arrow(up, M_PI / 2, 1135, 650);
// 	rot_arrow(up, M_PI / 2, 1065, 715);
// 	rot_arrow(up, M_PI / 2, 995, 650);
	
// }

void	draw_map(void)
{
	int i;

	i = 0;
	while (i < len * max_strs)
	{
		if ((i + 1)  % len != 0) //&& pnts[i].x >= 0 && pnts[i].y >= 0 && pnts[i].x <= 1200 && pnts[i].y <= 800)
		{
			if (fabs(pnts[i + 1].y - pnts[i].y) > fabs(pnts[i + 1].x - pnts[i].x))
				draw_lines_y(i, 1);
			else
				draw_lines_x(i, 1);
		}
			
		if ((i + len) < max_strs * len) /*&& pnts[len].x >= 0 && pnts[len].y >= 0 && pnts[len].x <= 1200 && pnts[len].y <= 800)*/
		{
			if (fabs(pnts[i + len].y - pnts[i].y) > fabs(pnts[i + len].x - pnts[i].x))
				draw_lines_y(i, len);
			else
				draw_lines_x(i, len);
		}
		i++;
	}
	draw_legend();

}

// t_vec	*copy_arrow()
// {
// 	t_vec *temp;
// 	int i;
// 	int j;
// 	int p;

// 	up = (t_vec*)malloc(sizeof(t_vec) * (1250));
// 	j = 0;
// 	p = 0;
// 	while (j < 25)
// 	{
// 		i = 0;
// 		while (i < 50)
// 		{
// 			temp[p].x = up[p].x;
// 			temp[p].y = up[p].y;
// 			temp[p].z = up[p].z;
// 			temp[p].color = up[p].color;
// 			p++;
// 			i++;
// 		}
// 		j++;
// 	}
// 	return (temp);
// }



// void get_arrows(void)
// {
// 	int fd;
// 	char *str;
// 	char **plot;
// 	char *num;
// 	int i;
// 	int j;
// 	int p;

// 	p = 0;
// 	ft_printf("In get Arrow\n");
// 	up = (t_vec*)malloc(sizeof(t_vec) * (1250));
// 	str = ft_strnew(2550);
// 	fd = open(arw_file, O_RDONLY);
// 	read(fd, str, 2550);
// 	close(fd);
// 	plot = ft_strsplit(str, '\n');
// 	ft_strdel(&str);
// 	j = 0;
// 	while (j < 25)
// 	{
// 		i = 0;
// 		while (i < 50)
// 		{
// 			plot[j] = ft_strtrim(plot[j]);
// 			if ((num  = ft_strchr(plot[j], ' ')) != NULL)
// 			{
// 				//num  = ft_strchr(map[j], ' ');
// 				if (num[1] == ' ')
// 					num++;
// 				num[0] = '\0';
// 				up[p].z = ft_atoi(plot[j]);
// 				free(plot[j]);
// 				plot[j] = ft_strdup(num + 1);
// 				up[p].color = up[p].z == 0 ? 0x000000 : 0x00FFFFFF;
// 				up[p].x = i;
// 				up[p].y = j;
// 			}
// 			else
// 			{
// 				up[p].z = ft_atoi(plot[j]);
// 				up[p].color = up[p].z == 0 ? 0x000000 : 0x00FFFFFF;
// 				up[p].x = i;
// 				up[p].y = j;

// 			}
// 			printf("map[%d] = %s\t",j, plot[j]);
// 			printf("X = %0.5f Y = %0.5f Z = %0.5f C = %d\t", up[p].x, up[p].y, up[p].z, up[p].color);
// 			p++;
// 			i++;
// 		}
// 		j++;
// 	}
// 	// down = copy_arrow();
// 	// left = copy_arrow();
// 	// right = copy_arrow();
// 	// rot_arrow(down, 1);
// 	// rot_arrow(left, 0.5);
// 	// rot_arrow(right, -0.5);

// }

void get_map(void)
{
	int fd;
	int j;
	
	// int i;
	int p = 0;
	char **map;
	char *temp;
	char **tmp;
	char *str;
	int i;

	int col;
	int next_space;
	char *num;
	// = ft_strnew(3);
	

	fd = open(file, O_RDONLY);
	j = 0;
	// ft_printf("Just before while\n");
	while (get_next_line(fd, &str) == 1)
	{
		if (j == 0)
		{
			tmp = ft_strsplit(str, ' ');
			temp = ft_strdup(str);

		}
		else
			temp = ft_strapp(temp, str);
		temp = ft_strapp(temp, ",");
		// ft_printf("temp = %s count = %d\n", temp, j);
		j++;
	}
	close(fd);
	max_strs = j;
	//map = (char**)malloc(sizeof(char*) * (max_strs) + 1);
	//map[max_strs] = NULL;
	map = ft_strsplit(temp, ',');
	len = ft_strlen(temp)/ max_strs + 1;
	// j = 0;
	// map = ft_strsplit(temp, '\n');
	// while (j < max_strs)
	// {
	// 	// map[j] = ft_strnew(len);
	// 	// map[j] = ft_strncpy(map[j], temp, len);
	// 	ft_printf("map[%d] = {%s}\n", j, map[j]);
	// 	// temp += len;
	// 	j++;
	// }
	j = 0;
	while (tmp[j] != NULL)
		j++;
	ft_strdel(tmp);
	ft_strdel(&temp);
	ft_printf("\nNumber of x points = %d\n", j);
	len = j;
	j = 0;

	pnts = (t_vec*)malloc(sizeof(t_vec) * (len * max_strs));
	// g_pnts = (t_vec*)malloc(sizeof(t_vec) * (len * max_strs));

	while (j  < max_strs)
	{
		i = 0;
		while (i  < len)
		{
			// g_pnts[p].x = 1;
			// g_pnts[p].y = 1;
			// g_pnts[p].z = 1;
			map[j] = ft_strtrim(map[j]);
			if ((num  = ft_strchr(map[j], ' ')) != NULL)
			{
				//num  = ft_strchr(map[j], ' ');
				if (num[1] == ' ')
					num++;
				num[0] = '\0';
				col = ft_atoi(map[j]);
				map[j] = ft_strdup(num + 1);
				// ft_printf("Setting Point\n");
				// points[p] = col;
				pnts[p].x = i;
				pnts[p].y = j;
				pnts[p].z = col;
				pnts[p].color =  colors[abs(col) % 24]; //colors[abs((24 + col) % 24)];
				//((255 % abs(col))<< 16) | ((255 % abs(col))<< 8) | (255 % abs(col));//colors[abs(col)];
				
				printf("Points: x = %f y = %f z = %f color = %d\n",pnts[p].x, pnts[p].y, pnts[p].z, pnts[p].color);
				// ft_printf(" %d ", *points);
				p++;
				// points[j / w][i / w] = col;
				
			}
			else
			{

				col = ft_atoi(map[j]);
				// points[p] = col;
				pnts[p].x = i;
				pnts[p].y = j;
				pnts[p].z = col;
				pnts[p].color =  colors[abs(col) % 24];//colors[abs((24+ col) % 24)];
				// 	pnts[p].color =  ((255 % abs(col))<< 16) | ((255 % abs(col))<< 8) | (255 % abs(col));//colors[abs(col)];
				// else
				// 	pnts[p].color = 0x00FFFFFF;
				p++;
			}
			i++;
		}
		j++;
	}
	translation_h(600 - (len / 2));
	translation_v(400 - (max_strs / 2));
	scale(w);
	ft_printf("\nLeaving get_grid\n");
	//scale(w);
	// translation_v(pad);
	// translation_h(pad);

	// i = 0;
	// ft_printf("\nPoints With len = %d\n", len);
	// while (i < len * max_strs)
	// {
	// 	if (i % len == 0)
	// 		ft_printf("\n");
	// 	// ft_printf("%d", points[i]);
	// 	printf("[%f,%f,%f]", pnts[i].x, pnts[i].y, pnts[i].z);
	// 	i++;
	// }
	// draw_map();
}



	// i = 0;
	// while (i < len * max_strs)
	// {
	// 	if ((i + len) < max_strs)
	// 		draw_lines_y(i);
	// 	i++;
	// }

// int my_loop_hook(void *mlx)
// {
// 	mlx_key_hook(win, my_key_funct, mlx);
// }
int my_key_pressed(int keycode, void *mlx)
{
	if (keycode == 0)
		flags |= rot_x;
	else if (keycode == 1)
		flags |= rot_x | sign;
	else if (keycode == 2)
		flags |= rot_y;
	else if (keycode == 3)
		flags |= rot_y | sign;
	else if (keycode == 6)
		flags |= rot_z;
	else if (keycode == 7)
		flags |= rot_z | sign;
	// else if (keycode == 75)
	// 	perspective(0.5);
	// else if (keycode == 67)
	// 	perspective(2);
	// else if (keycode == 78)
	// 	perspective(-1);
	else if (keycode == 24)
		flags |= scl;
	else if (keycode == 27)
		flags |= scl | sign;
	else if (keycode == 123)
		flags |= tran_h;
	else if (keycode == 124)
		flags |= tran_h | sign;
	else if (keycode == 125)
		flags |= tran_v;
	else if (keycode == 126)
		flags |= tran_v | sign;
	// else if (keycode == 53)
	// 	exit(1);
	// else if (keycode == 15)
	// {
	// 	ft_bzero((void *)keys, 100);
	// 	key_len = 0;
	// 	get_map();
	// }
	// mlx_clear_window(mlx, win);
	// draw_map();
	// if ((keycode >= 0 && keycode <= 7) || keycode == 24 || keycode == 27 || 
	// 	(keycode >= 123 && keycode <= 126))
	// {
	// 	clear();
	// 	draw_map();
	// }
	return (0);
}

int my_loop_hook(void *mlx)
{
	if (flags & rot_x)
	{
		if (flags & sign)
			rotation_x(-0.125);
		else
			rotation_x(0.125);
	}
	else if (flags & rot_y)
	{
		if (flags & sign)
			rotation_y(-0.125);
		else
			rotation_y(0.125);
	}
	else if (flags & rot_z)
	{
		if (flags & sign)
			rotation_z(-0.125);
		else
			rotation_z(0.125);
	}
	else if (flags & tran_v)
	{
		if (flags & sign)
			translation_v(-10.0);
		else
			translation_v(10.0);
	}
	else if (flags & tran_h)
	{
		if (flags & sign)
			translation_h(-10.0);
		else
			translation_h(10);
	}
	else if (flags & scl)
	{
		if (flags & sign)
			scale(0.8);
		else
			scale(1.25);
	}
	if (flags)
	{
		keys[key_len] = flags;
		key_len++;
		mlx_clear_window(mlx, win);
		draw_map();
	}
	
	return (0);
}
int my_mouse_released(int button, int i, int j, void *mlx)
{
	if (flags & mous)
		flags = 0;
	return (0);
}
int my_mouse_function(int button, int i, int j, void *mlx)
{
	ft_printf("Button = %d  X = %d  Y  = %d\n", button, i, j);
	if ( (j - 590) - (i - 1050) >= -40 && (j - 590) + (i - 1050) >= 40 && (j - 590) <= 40)
		flags |= rot_x | mous;
	else if ((j - 650) + (i - 1150) <= 80 && (j - 650) >= (i - 1150) && (i - 1150 >= 0))
		flags |= rot_y | sign | mous;
	else if ((j - 750) + (i - 1050) <= 80 && (j - 750) <= (i - 1050) && (j - 750) >= 0)
		flags |= rot_x | sign | mous;
	else if ((j - 650) + (i - 990) >= 40 && (j - 650) - (i - 990) <= 40 && (i - 990) <= 40)
		flags |= rot_y | mous;;
	return (0);
}


int main(int argc, char **argv)
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1200, 800, "mlx_42");
	init_colors();
	keys = (unsigned char *)ft_strnew(1024);
	if (argc >= 2)
	{
		// ft_printf("Calling draw map\n");
		file = argv[1];
		get_map();
		draw_map();
		

		// if (argc == 3)
		// {
		// 	arw_file = argv[2];
		// 	get_arrows();
		// 	draw_arrows();
			
		// }

	}
	
	// void *img;
	// int x = 0; 
	// int y = 0;
	// img = mlx_xpm_file_to_image(mlx, "test_maps/42.fdf", &x, &y);
	// img = mlx_new_image(mlx, 800, 600);
	
	
	//mlx_put_image_to_window(mlx, win, img, 0, 0);
	// mlx_loop_hook(mlx, my_loop_hook, win);
	// mlx_key_pressed_hook(win, my_key_pressed, mlx);
	mlx_key_hook(win, my_key_funct, mlx);
	mlx_hook(win, 2, 0, my_key_pressed, mlx);
	mlx_hook(win, 5, 0, my_mouse_released, mlx);
	mlx_mouse_hook(win, my_mouse_function, mlx);
	mlx_loop_hook(mlx, my_loop_hook, win);
	mlx_loop(mlx);
	
}
