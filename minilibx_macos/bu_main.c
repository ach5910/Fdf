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
char **map;
int *points;
// char **points;
int color = 0x00FFFFFF;
int len;

int w = 50;
int pad = 100;

typedef struct s_vec
{
	int	x;
	int y;
	int	z;
}				t_vec;
t_vec *pnts;


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
int my_key_funct(int keycode, void *mlx)
{
	printf("key event %d\n", keycode);
	if (keycode == 0)
		draw(0x00000010);
	else if (keycode == 1)
		draw(-0x00000010);
	else if (keycode == 2)
		draw(0x00001000);
	else if (keycode == 3)
		draw(-0x00001000);
	else if (keycode == 5)
		draw(0x00100000);
	else if (keycode == 4)
		draw(-0x00100000);
	return (0);
}

void draw_lines_x(int index)
{
	int dx = pnts[index + 1].x - pnts[index].x;
	int dy = pnts[index + 1].y - pnts[index].y;
	double p = (2 * dy) - dx;
	int i = pnts[index].x;
	int j = pnts[index].y;
	double ci;
	double cf;

	// if (pnts[index].z == pnts[index + 1].z && pnts[index].z != 0)
	// {
	// 	if (pnts[index].z == 1)
	// 		color = 0x191970;
	// 	if (pnts[index].z == 2)
	// 		color = 0x87ceeb;
	// 	if (pnts[index].z == 3)
	// 		color = 0x32cd32;
	// 	if (pnts[index].z == 5)
	// 		color = 0x228b22;
	// 	if (pnts[index].z == 7)
	// 		color = 0xffff00;
	// 	if (pnts[index].z == 10)
	// 		color = 0x8b0000;
	// 	if (pnts[index].z == 15)
	// 		color = 0xd2b48c;
	// 	if (pnts[index].z == 20)
	// 		color = 0xffa500;
	// }
	// else
	// 	color = 0x00FFFFFF;

	if (pnts[index].z == 0)
		ci = 0x00FFFFFF;
	else
		ci = 0x8b0000;
	if (pnts[index + 1].z == 0)
		cf = 0x00FFFFFF;
	else
		cf = 0x8b0000;
	while (i < pnts[index + 1].x)
	{
		color = ci + (cf - ci) * ((double)pnts[index + 1].x - (double)i) / (double)dx;
		mlx_pixel_put(mlx, win, i + pad , j + pad , color);
		// mlx_pixel_put(mlx, win, i, j, color);
		if (p < 0)
		{
			p += (2 * dy);
		}
		else
		{
			p += (2 * dy) - (2 * dx);
			j++;
		}
		i++;
	}
}

void draw_lines_y(int index)
{
	int dx = pnts[index + len].x - pnts[index].x;
	int dy = pnts[index + len].y - pnts[index].y;
	double p = (2 * dx) - dy;
	int i = pnts[index].y;
	int j = pnts[index].x;
	double ci;
	double cf;

	// if (pnts[index].z != 0)
	// 	mlx_pixel_put(mlx, win, j + pad , i + pad , 0x8b0000);
	// else
	// 	mlx_pixel_put(mlx, win, j + pad , i + pad , 0x00FFFFFF);
	// i++;
	// if (pnts[index].z == pnts[index + len].z && pnts[index].z != 0)
	// {
	// 	if (pnts[index].z == 1)
	// 		color = 0x191970;
	// 	if (pnts[index].z == 2)
	// 		color = 0x87ceeb;
	// 	if (pnts[index].z == 3)
	// 		color = 0x32cd32;
	// 	if (pnts[index].z == 5)
	// 		color = 0x228b22;
	// 	if (pnts[index].z == 7)
	// 		color = 0xffff00;
	// 	if (pnts[index].z == 10)
	// 		color = 0x8b0000;
	// 	if (pnts[index].z == 15)
	// 		color = 0xd2b48c;
	// 	if (pnts[index].z == 20)
	// 		color = 0xffa500;
	// }
	// else
	// 	color = 0x00FFFFFF;

	if (pnts[index].z == 0)
		ci = 0x00FFFFFF;
	else
		ci = 0x8b0000;
	if (pnts[index + len].z == 0)
		cf = 0x00FFFFFF;
	else
		cf = 0x8b0000;
	while (i < pnts[index + len].y)
	{
		color = ci + (cf - ci) * ((double)pnts[index + len].y - (double)i) / (double)dy;
		mlx_pixel_put(mlx, win, j + pad , i + pad , color);
		// mlx_pixel_put(mlx, win, i, j, color);
		if (p < 0)
		{
			p += (2 * dx);
		}
		else
		{
			p += (2 * dx) - (2 * dy);
			j++;
		}
		i++;
	}
}

void draw_map(char *file)
{
	int fd;
	int j;
	int max_strs;
	// int i;
	int p = 0;
	
	char *temp;
	char **tmp;
	char *str;
	int i;

	int col;
	int next_space;
	char *num = ft_strnew(3);
	

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
		// ft_printf("temp = %s count = %d\n", temp, j);
		j++;
	}
	max_strs = j;
	map = (char**)malloc(sizeof(char*) * (max_strs) + 1);
	map[max_strs] = NULL;
	len = ft_strlen(temp) / max_strs;
	j = 0;
	// map = ft_strsplit(temp, '\n');
	while (j < max_strs)
	{
		map[j] = ft_strnew(len);
		map[j] = ft_strncpy(map[j], temp, len);
		ft_printf("map[%d] = {%s}\n", j, map[j]);
		temp += len;
		j++;
	}
	j = 0;
	while (tmp[j] != NULL)
		j++;
	ft_printf("\nNumber of x points = %d\n", j);
	len = j;
	j = 0;
	// points = (char**)malloc(sizeof(char*) * (max_strs) + 1);
	// points[max_strs] = NULL;
	// len = (len - 1) / 3;
	points = (int*)malloc(sizeof(int) * (len * max_strs + 1));
	pnts = (t_vec*)malloc(sizeof(t_vec) * (len * max_strs));

	// while (j  / w < max_strs)
	// {
	// 	i = 0;
	// 	while (i / w < len)
	// 	{
	// 		if (i % w == 0 && j % w == 0)
	// 		{
	// 			num  = ft_strchr(map[j / w], ' ');
	// 			if (num[1] == ' ')
	// 				num++;
	// 			num[0] = '\0';
	// 			col = ft_atoi(map[j / w]);
	// 			map[j / w] = ft_strdup(num + 1);
	// 			// ft_printf(" %d ", col);
	// 			points[p] = col;
	// 			// ft_printf(" %d ", *points);
	// 			p++;
	// 			// points[j / w][i / w] = col;
				
	// 		}
	// 		// if (j == 20)
	// 		// 	ft_printf("num = %s col = %d\n", num, col);
	// 		// ft_printf("n = %s c = %d", num, col);
	// 		if (col == 10)
	// 		{
	// 			// ft_printf("color = %d i = %d j = %d\n", col, i, j);
	// 			color = 0x8b0000;
	// 		}
	// 		else
	// 			color = 0xFFFFFF;
				
	// 		if (i % w == 0 || j % w == 0)
	// 			mlx_pixel_put(mlx, win, i + pad, j + pad, color);

	// 		// while (!ft_isdigit(**map))
	// 		// {
	// 		// 	(*map)++;
	// 		// }
	// 		i++;
	// 	}
	// 	// acol = 0;
	// 	// ft_printf("\n");
	// 	j++;
	// }

	while (j  < max_strs)
	{
		i = 0;
		while (i  < len)
		{
			if ((num  = ft_strchr(map[j], ' ')) != NULL)
			{
				//num  = ft_strchr(map[j], ' ');
				if (num[1] == ' ')
					num++;
				num[0] = '\0';
				col = ft_atoi(map[j]);
				map[j] = ft_strdup(num + 1);
				// ft_printf(" %d ", col);
				points[p] = col;
				pnts[p].x = i * w;
				pnts[p].y = j * w;
				pnts[p].z = col;
				// ft_printf(" %d ", *points);
				p++;
				// points[j / w][i / w] = col;
				
			}
			else
			{

				col = ft_atoi(map[j]);
				points[p] = col;
				pnts[p].x = i * w;
				pnts[p].y = j * w;
				pnts[p].z = col;
				p++;
			}
			// ß
			// if (j == 20)
			// 	ft_printf("num = %s col = %d\n", num, col);
			// ft_printf("n = %s c = %d", num, col);
			if (col == 10)
			{
				// ft_printf("color = %d i = %d j = %d\n", col, i, j);
				color = 0x8b0000;
			}
			else
				color = 0xFFFFFF;
				
			// if (i % w == 0 || j % w == 0)
			//mlx_pixel_put(mlx, win, i * w + pad, j * w + pad, color);

			// while (!ft_isdigit(**map))
			// {
			// 	(*map)++;
			// }
			i++;
		}
		// acol = 0;
		// ft_printf("\n");
		j++;
	}

	i = 0;
	ft_printf("\nPoints With len = %d\n", len);
	while (i < len * max_strs)
	{
		if (i % len == 0)
			ft_printf("\n");
		// ft_printf("%d", points[i]);
		ft_printf("[%d,%d,%d]", pnts[i].x, pnts[i].y, pnts[i].z);
		i++;
	}

	i = 0;
	while (i < len * max_strs)
	{
		if ((i + 1)  % len != 0)
			draw_lines_x(i);
		if ((i + len) < max_strs * len)
			draw_lines_y(i);
		i++;
	}

	// i = 0;
	// while (i < len * max_strs)
	// {
	// 	if ((i + len) < max_strs)
	// 		draw_lines_y(i);
	// 	i++;
	// }
}

int main(int argc, char **argv)
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1200, 800, "mlx_42");
	if (argc == 2)
	{
		// ft_printf("Calling draw map\n");
		draw_map(argv[1]);

	}
	
	// void *img;
	// int x = 0; 
	// int y = 0;
	// img = mlx_xpm_file_to_image(mlx, "test_maps/42.fdf", &x, &y);
	// img = mlx_new_image(mlx, 800, 600);
	
	
	//mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_key_hook(win, my_key_funct, mlx);
	mlx_loop(mlx);
	
}
