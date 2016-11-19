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
#define WIDTH 1200
#define HEIGHT 800
void *win;
void *mlx;

//int *points;
// char **points;
int color = 0x00FFFFFF;
int len;
int max_strs;
int w = 10;
int pad = 150;
int key_len = 0;
int iter = 0;
char *file;
char **files;
int max_files = 0;
int file_num = 0;
double c_min;
double c_max;
char *arw_file;
unsigned int *keys;
double per = 1;
//int col_iter = 0;

const unsigned int tran_h = 0x01;
const unsigned int tran_v = 0x02;
const unsigned int scl = 0x04;
const unsigned int rot_x = 0x08;
const unsigned int rot_y = 0x10;
const unsigned int rot_z = 0x20;
const unsigned int mous = 0x40;
const unsigned int sign = 0x80;
const unsigned int rot_x_neg = 0x100;
const unsigned int rot_y_neg = 0x200;
unsigned int flags = 0;

typedef struct s_vec
{
	double	x;
	double y;
	double	z;
	int color;
}				t_vec;
t_vec *pnts;
t_vec *c_pnts;

void get_map(char *file_name);
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
void set_color_map(int get_next_map);
void reset_map(void);

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

char *theme_names[7] = {"Dawn","Dusk","Kryptonite","Red Blue","Fire","Ice","Seashore"};

int dawn[64] = {
	0xffffc3, 0xffffbe, 0xffffba, 0xffffb6, 
	0xffffb1, 0xffffad, 0xffffa9, 0xffffa4,
	0xffffa0, 0xffff9b, 0xffff97, 0xffff93, 
	0xffff8e, 0xffff8a, 0xffff86, 0xffff81, 
	0xffff7d, 0xfff77d, 0xffee7d, 0xffe77d, 
	0xffdf7e, 0xffd77e, 0xffcf7e, 0xffc77e, 
	0xffbf7e, 0xffb77e, 0xffaf7e, 0xffa77e, 
	0xff9f7e, 0xff977e, 0xff8f7f, 0xff867f, 
	0xfe7e7f, 0xf6767f, 0xee6f7f, 0xe6667f, 
	0xde5e7f, 0xd6577f, 0xce4f7f, 0xc6467f, 
	0xbe3f7f, 0xb6367f, 0xae2f7f, 0xa5277f, 
	0x9d1f7f, 0x95167f, 0x8d0e7f, 0x85067f, 
	0x7d007f, 0x75007f, 0x6d007f, 0x65007f, 
	0x5d007f, 0x55007e, 0x4e007e, 0x46007e, 
	0x3e007e, 0x36007e, 0x2e007e, 0x26007e, 
	0x1e007e, 0x16007e, 0xe007e,  0x6007e};

int dawn_center[64] = {
	0xffff7d, 0xfffb7d, 0xfff77d, 0xfff27d, 
	0xffee7d, 0xffeb7d, 0xffe77d, 0xffe37e, 
	0xffdf7e, 0xffdb7e, 0xffd77e, 0xffd37e, 
	0xffcf7e, 0xffcb7e, 0xffc77e, 0xffc37e, 
	0xffbf7e, 0xffbb7e, 0xffb77e, 0xffb37e, 
	0xffaf7e, 0xffab7e, 0xffa77e, 0xffa37e, 
	0xff9f7e, 0xff9b7e, 0xff977e, 0xff937e, 
	0xff8f7f, 0xff8a7f, 0xff867f, 0xff837f, 
	0xfe7e7f, 0xfa7a7f, 0xf6767f, 0xf2737f, 
	0xee6f7f, 0xea6b7f, 0xe6667f, 0xe2627f, 
	0xde5e7f, 0xda5b7f, 0xd6577f, 0xd2537f, 
	0xce4f7f, 0xca4b7f, 0xc6467f, 0xc2427f, 
	0xbe3f7f, 0xba3b7f, 0xb6367f, 0xb2337f, 
	0xae2f7f, 0xa92a7f, 0xa5277f, 0xa1227f, 
	0x9d1f7f, 0x991b7f, 0x95167f, 0x91127f, 
	0x8d0e7f, 0x890b7f, 0x85067f, 0x81027f};

int dusk[64] = {
	0xffffff, 0xfff7ff, 0xffefff, 0xffe7ff, 
	0xffdfff, 0xffd7ff, 0xffcfff, 0xffc7ff, 
	0xffbfff, 0xffb7ff, 0xffafff, 0xffa8ff, 
	0xffa0ff, 0xff98ff, 0xff90ff, 0xff88ff, 
	0xff80ff, 0xf778ff, 0xee70ff, 0xe768ff, 
	0xdf60ff, 0xd758ff, 0xcf4fff, 0xc747ff, 
	0xbf3fff, 0xb737ff, 0xaf2fff, 0xa727ff, 
	0x9f1fff, 0x9717ff, 0x8f0fff, 0x8607ff, 
	0x7e00fe, 0x7600f6, 0x6f00ee, 0x6600e6, 
	0x5e00df, 0x5700d7, 0x4f00cf, 0x4600c7, 
	0x3f00bf, 0x3600b7, 0x2f00af, 0x2700a8, 
	0x1f00a0, 0x160098, 0xe0090, 0x60088, 
	0x80, 	  0x78,     0x70,     0x68, 
	0x60,     0x58,     0x4f,     0x47, 
	0x3f,     0x37,     0x2f,     0x27, 
	0x1f,     0x16,     0xe,       0x6};

int kryptonite[64] = {
	0xffffff, 0xfffff7, 0xffffef, 0xffffe7, 
	0xffffdf, 0xffffd7, 0xffffcf, 0xffffc7, 
	0xffffbf, 0xffffb7, 0xffffaf, 0xffffa8, 
	0xffffa0, 0xffff98, 0xffff90, 0xffff88, 
	0xffff80, 0xf7ff78, 0xeeff70, 0xe7ff68, 
	0xdfff60, 0xd7ff58, 0xcfff4f, 0xc7ff47, 
	0xbfff3f, 0xb7ff37, 0xafff2f, 0xa7ff27, 
	0x9fff1f, 0x97ff17, 0x8fff0f, 0x86ff07, 
	0x7efe00, 0x76f600, 0x6fee00, 0x66e600, 
	0x5edf00, 0x57d700, 0x4fcf00, 0x46c700, 
	0x3fbf00, 0x36b700, 0x2faf00, 0x27a800, 
	0x1fa000, 0x169800, 0xe9000,  0x68800, 
	0x8000,   0x7800,   0x7000,   0x6800, 
	0x6000,   0x5800,   0x4f00,   0x4700, 
	0x3f00,   0x3700,   0x2f00,   0x2700, 
	0x1f00,   0x1600,   0xe00,    0x600};

int kryptonite_center[64] = {
	0xffff80, 0xfbff7c, 0xf7ff78, 0xf2ff74, 
	0xeeff70, 0xebff6c, 0xe7ff68, 0xe3ff64, 
	0xdfff60, 0xdbff5c, 0xd7ff58, 0xd3ff54, 
	0xcfff4f, 0xcbff4b, 0xc7ff47, 0xc3ff43, 
	0xbfff3f, 0xbbff3b, 0xb7ff37, 0xb3ff33, 
	0xafff2f, 0xabff2b, 0xa7ff27, 0xa3ff23, 
	0x9fff1f, 0x9bff1b, 0x97ff17, 0x93ff13, 
	0x8fff0f, 0x8aff0b, 0x86ff07, 0x83ff03, 
	0x7efe00, 0x7afa00, 0x76f600, 0x73f200, 
	0x6fee00, 0x6bea00, 0x66e600, 0x62e300, 
	0x5edf00, 0x5bdb00, 0x57d700, 0x53d300, 
	0x4fcf00, 0x4bcb00, 0x46c700, 0x42c300, 
	0x3fbf00, 0x3bbb00, 0x36b700, 0x33b300, 
	0x2faf00, 0x2aac00, 0x27a800, 0x22a400, 
	0x1fa000, 0x1b9c00, 0x169800, 0x129400, 
	0xe9000,  0xb8c00,  0x68800,  0x28400,};

int red_blue[64] = {
	0x5f0000, 0x650000, 0x6b0000, 0x720000, 
	0x780000, 0x7e0000, 0x840000, 0x8a0000, 
	0x900000, 0x960000, 0x9d0000, 0xa30000, 
	0xa90000, 0xaf0000, 0xb50000, 0xbb0000, 
	0xc10101, 0xc51111, 0xc92121, 0xcd3131, 
	0xd14141, 0xd55151, 0xd96161, 0xdd7171, 
	0xe08181, 0xe49191, 0xe8a1a1, 0xecb1b1, 
	0xf0c1c1, 0xf4d1d1, 0xf8e1e1, 0xfcf1f1, 
	0xfdfdff, 0xededfb, 0xddddf7, 0xcdcdf3, 
	0xbdbdef, 0xadadec, 0x9d9de8, 0x8d8de4, 
	0x7d7de0, 0x6d6ddc, 0x5d5dd9, 0x4d4dd5, 
	0x3d3dd1, 0x2d2dcd, 0x1d1dca, 0xd0dc6, 
	0xc2, 	  0xbb,     0xb5, 	  0xaf, 
	0xa9, 	  0xa2, 	0x9c, 	  0x96, 
	0x90, 	  0x89, 	0x83, 	  0x7d, 
	0x77, 	  0x70, 	0x6a, 	  0x64};

int fire[64] =
{
	0xffffff, 0xfffff7, 0xffffef, 0xffffe7, 
	0xffffdf, 0xffffd7, 0xffffcf, 0xffffc7, 
	0xffffbf, 0xffffb7, 0xffffaf, 0xffffa8, 
	0xffffa0, 0xffff98, 0xffff90, 0xffff88, 
	0xffff80, 0xfff778, 0xffee70, 0xffe768, 
	0xffdf60, 0xffd758, 0xffcf4f, 0xffc747, 
	0xffbf3f, 0xffb737, 0xffaf2f, 0xffa727, 
	0xff9f1f, 0xff9717, 0xff8f0f, 0xff8607, 
	0xfe7e00, 0xf67600, 0xee6f00, 0xe66600, 
	0xdf5e00, 0xd75700, 0xcf4f00, 0xc74600, 
	0xbf3f00, 0xb73600, 0xaf2f00, 0xa82700, 
	0xa01f00, 0x981600, 0x900e00, 0x880600, 
	0x800000, 0x780000, 0x700000, 0x680000, 
	0x600000, 0x580000, 0x4f0000, 0x470000, 
	0x3f0000, 0x370000, 0x2f0000, 0x270000, 
	0x1f0000, 0x160000, 0xe0000,  0x60000};

int fire_center[64] = {
	0xffff80, 0xfffb7c, 0xfff778, 0xfff274, 
	0xffee70, 0xffeb6c, 0xffe768, 0xffe364, 
	0xffdf60, 0xffdb5c, 0xffd758, 0xffd354, 
	0xffcf4f, 0xffcb4b, 0xffc747, 0xffc343, 
	0xffbf3f, 0xffbb3b, 0xffb737, 0xffb333, 
	0xffaf2f, 0xffab2b, 0xffa727, 0xffa323, 
	0xff9f1f, 0xff9b1b, 0xff9717, 0xff9313, 
	0xff8f0f, 0xff8a0b, 0xff8607, 0xff8303, 
	0xfe7e00, 0xfa7a00, 0xf67600, 0xf27300, 
	0xee6f00, 0xea6b00, 0xe66600, 0xe36200, 
	0xdf5e00, 0xdb5b00, 0xd75700, 0xd35300, 
	0xcf4f00, 0xcb4b00, 0xc74600, 0xc34200, 
	0xbf3f00, 0xbb3b00, 0xb73600, 0xb33300, 
	0xaf2f00, 0xac2a00, 0xa82700, 0xa42200, 
	0xa01f00, 0x9c1b00, 0x981600, 0x941200, 
	0x900e00, 0x8c0b00, 0x880600, 0x840200};

int ice[64] = {
	0xffffff, 0xf7ffff, 0xefffff, 0xe7ffff,
	0xdfffff, 0xd7ffff, 0xcfffff, 0xc7ffff, 
	0xbfffff, 0xb7ffff, 0xafffff, 0xa8ffff, 
	0xa0ffff, 0x98ffff, 0x90ffff, 0x88ffff, 
	0x80ffff, 0x78f7ff, 0x70eeff, 0x68e7ff, 
	0x60dfff, 0x58d7ff, 0x4fcfff, 0x47c7ff, 
	0x3fbfff, 0x37b7ff, 0x2fafff, 0x27a7ff, 
	0x1f9fff, 0x1797ff, 0xf8fff,  0x786ff, 
	0x7efe,   0x76f6,   0x6fee,   0x66e6, 
	0x5edf,   0x57d7,   0x4fcf,   0x46c7, 
	0x3fbf,   0x36b7,   0x2faf,   0x27a8,   
	0x1fa0,   0x1698,   0xe90,    0x688,
	0x80,     0x78,     0x70, 	  0x68,     
	0x60,     0x58,     0x4f, 	  0x47,     
	0x3f,     0x37,     0x2f,	  0x27,
	0x1f,     0x16,     0xe,      0x6};

int seashore[64] = 
{
	0xffffc3, 0xffffbe, 0xffffba, 0xffffb6,
	0xffffb1, 0xffffad, 0xffffa9, 0xffffa4, 
	0xffffa0, 0xffff9b, 0xffff97, 0xffff93, 
	0xffff8e, 0xffff8a, 0xffff86, 0xffff81, 
	0xffff7d, 0xf7ff7d, 0xeeff7d, 0xe7ff7d, 
	0xdfff7e, 0xd7ff7e, 0xcfff7e, 0xc7ff7e, 
	0xbfff7e, 0xb7ff7e, 0xafff7e, 0xa7ff7e, 
	0x9fff7e, 0x97ff7e, 0x8fff7f, 0x86ff7f, 
	0x7efe7f, 0x76f67f, 0x6fee7f, 0x66e67f, 
	0x5ede7f, 0x57d67f, 0x4fce7f, 0x46c67f, 
	0x3fbe7f, 0x36b67f, 0x2fae7f, 0x27a57f, 
	0x1f9d7f, 0x16957f, 0xe8d7f,  0x6857f, 
	0x7d7f,   0x757f,   0x6d7f,   0x657f, 
	0x5d7f,   0x557e,   0x4e7e,   0x467e,
	0x3e7e,   0x367e,   0x2e7e,   0x267e, 
	0x1e7e,   0x167e,   0xe7e,    0x67e};

int seashore_center[64] = {
	0xffff7d, 0xfbff7d, 0xf7ff7d, 0xf2ff7d, 
	0xeeff7d, 0xebff7d, 0xe7ff7d, 0xe3ff7e, 
	0xdfff7e, 0xdbff7e, 0xd7ff7e, 0xd3ff7e, 
	0xcfff7e, 0xcbff7e, 0xc7ff7e, 0xc3ff7e, 
	0xbfff7e, 0xbbff7e, 0xb7ff7e, 0xb3ff7e, 
	0xafff7e, 0xabff7e, 0xa7ff7e, 0xa3ff7e, 
	0x9fff7e, 0x9bff7e, 0x97ff7e, 0x93ff7e, 
	0x8fff7f, 0x8aff7f, 0x86ff7f, 0x83ff7f, 
	0x7efe7f, 0x7afa7f, 0x76f67f, 0x73f27f, 
	0x6fee7f, 0x6bea7f, 0x66e67f, 0x62e27f, 
	0x5ede7f, 0x5bda7f, 0x57d67f, 0x53d27f, 
	0x4fce7f, 0x4bca7f, 0x46c67f, 0x42c27f, 
	0x3fbe7f, 0x3bba7f, 0x36b67f, 0x33b27f, 
	0x2fae7f, 0x2aa97f, 0x27a57f, 0x22a17f, 
	0x1f9d7f, 0x1b997f, 0x16957f, 0x12917f, 
	0xe8d7f,  0xb897f,  0x6857f,  0x2817f};

//int **color_theme = {&dawn, &dusk, &kryptonite, &red_blue, &fire, &ice, &seashore};
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

int my_key_recall(unsigned int keycode, void *mlx)
{
	printf("key event %d\n", keycode);
	
	if (keycode & rot_x_neg)
		rotation_x(-0.125);
	if (keycode & rot_y_neg)
		rotation_y(-0.125);
	if (keycode & rot_x)
		rotation_x(0.125);
	if (keycode & rot_y)
		rotation_y(0.125);
	if (keycode & sign)
	{
		if (keycode & rot_z)
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
		if (keycode & rot_z)
			rotation_z(0.125);
		else if (keycode & scl)
			scale(1.25);
		else if (keycode & tran_h)
			translation_h(10.0);
		else if (keycode & tran_v)
			translation_v(10.0);
	}
	return (0);
}

int my_key_funct(int kc, void *mlx)
{
	if (flags && !(flags & mous))
		flags = 0;
	if (kc == 75)
		perspective(0.5);
	else if (kc == 67)
		perspective(2);
	else if (kc == 78)
		perspective(-1);
	else if (kc == 53)
		exit(1);
	else if (kc == 15)
	{
		ft_bzero((void *)keys, 1024);
		key_len = 0;
		reset_map();
		mlx_clear_window(mlx, win);
		set_color_map(0);
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
}

void scale(double factor)
{
	int i;

	i = 0;
	double center_x = WIDTH / 2;
	double center_y = HEIGHT / 2;
	while (i < len * max_strs)
	{
		pnts[i].x = center_x + factor * (pnts[i].x - center_x);
		pnts[i].y = center_y + factor * (pnts[i].y - center_y);
		pnts[i].z *= factor;
		i++;
	}
}
void	perspective(double dir)
{
	int i;
	int end;

	per *= dir;
	mlx_clear_window(mlx, win);
	reset_map();
	i = 0;
	while (i < len * max_strs)
	{
		pnts[i].z = per * pnts[i].z;
		// temp_z = pnts[i].z == 0 ? 1 : pnts[i].z;
		// pnts[i].x = 0.5 * pnts[i].x / temp_z;
		// pnts[i].y = 0.5 * pnts[i].y / temp_z;
		i++;
	}
	
	i = 0;
	while (i < key_len)
	{
		my_key_recall((int)keys[i], mlx);
		i++;
	}

	set_color_map(0);	
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
	
	while (i < pnts[end].x)
	{
		color = ci + (cf - ci) * (i - pnts[start].x) / dx;
		mlx_pixel_put(mlx, win, (i), (j), color);
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

	end = pnts[index + inc].y > pnts[index].y ? index + inc : index;
	start = pnts[index + inc].y > pnts[index].y ? index : index + inc;
	i = pnts[start].y;
	j = pnts[start].x;
	j_incr = pnts[end].x > pnts[start].x ? 1 : -1;
	ci = pnts[start].color;
	cf = pnts[end].color;

	
	mlx_pixel_put(mlx, win, (j) , (i) , pnts[index].color);
	i++;

	while (i < pnts[end].y)
	{
		color = ci + (cf - ci) * (i - pnts[start].y) / dy;
		//color = color_map[(int)(((c_max - c_pnts[i].z)/ (c_max - c_min)) * 63)];
		mlx_pixel_put(mlx, win, (j), (i), color);
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

void draw_legend(void)
{
	int white;
	//char *color_theme;

	draw_tri();
	mlx_string_put(mlx, win, 30, 25, 16777215 , "***TRANSFORMATION COMMANDS***");
	mlx_string_put(mlx, win, 30, 50, 16777215, "Exit  		: 'ESC'");
	mlx_string_put(mlx, win, 30, 70, 16777215 , "Reset 		: 'r'");
	mlx_string_put(mlx, win, 30, 90, 16777215 , "Scale 		: '-'  '+' (Keypad)");
	mlx_string_put(mlx, win, 30, 110, 16777215 , "Depth 		: '*'  '/'  '-' (Numpad)");
	mlx_string_put(mlx, win, 30, 130, 16777215 ,"Translation : 'Arrows'");
	mlx_string_put(mlx, win, 30, 150, 16777215 ,"Rotation 	:");
	mlx_string_put(mlx, win, 30, 170, 16777215 ,"     x - 'd'  'f'");
	mlx_string_put(mlx, win, 30, 190, 16777215 ,"     y - 'a'  's'");
	mlx_string_put(mlx, win, 30, 210, 16777215 ,"     z - 'z'  'x'");

	//color_theme = ft_strjoin("Color Theme : ", theme_names[col_iter % 7]);
	//mlx_string_put(mlx, win, WIDTH - 200, 25, 16777215, color_theme);
	// ft_printf("Color Theme: %s", theme_names[col_iter % 7]);

	// mlx_string_put(mlx, win, 30, 25, 16777215 - (iter % 10 * (7667711) + (iter / 2) * (7667711), "***TRANSFORMATION COMMANDS***");
	// mlx_string_put(mlx, win, 30, 50, 16777215 - (iter / 2) * (7667711) + (iter / 3) * (7667711), "Exit  		: 'ESC'");
	// mlx_string_put(mlx, win, 30, 70, 16777215 - (iter / 3) * (7667711) + (iter / 4) * (7667711), "Reset 		: 'r'");
	// mlx_string_put(mlx, win, 30, 90, 16777215 - (iter / 4) * (7667711) + (iter / 5) * (7667711), "Scale 		: '-'  '+' (Keypad)");
	// mlx_string_put(mlx, win, 30, 110, 16777215 - (iter / 5) * (7667711) + (iter / 6) * (7667711), "Depth 		: '*'  '/'  '-' (Numpad)");
	// mlx_string_put(mlx, win, 30, 130, 16777215 - (iter / 6) * (7667711) + (iter / 7) * (7667711),"Translation : 'Arrows'");
	// mlx_string_put(mlx, win, 30, 150, 16777215 - (iter / 7) * (7667711) + (iter / 8) * (7667711),"Rotation 	:");
	// mlx_string_put(mlx, win, 30, 170, 16777215 - (iter / 8) * (7667711) + (iter / 9) * (7667711),"     x - 'd'  'f'");
	// mlx_string_put(mlx, win, 30, 190, 16777215 - (iter / 9) * (7667711) + (iter / 10) * (7667711),"     y - 'a'  's'");
	// mlx_string_put(mlx, win, 30, 210, 16777215 - (iter / 10) * (7667711) + (iter / 11) * (7667711),"     z - 'z'  'x'");
}

void apply_color_map(int *color_map)
{
	int i;

	if (c_max - c_min == 0)
	{
		i = 0;
		while (i < len * max_strs)
		{
			pnts[i].color = 0x00FFFFFF;
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < len * max_strs)
		{
			pnts[i].color = color_map[(int)(((c_max - c_pnts[i].z)/ (c_max - c_min)) * 63)];
			// printf("Color Ratio = %f\n", ((c_pnts[i].z - c_min)/ (c_max - c_min)));
			i++;
		}
	}
}

void set_color_map(int get_next_map)
{
	static int col_iter = 0;

	col_iter += get_next_map;
	if (col_iter % 11 == 0)
		apply_color_map(dawn);
	else if (col_iter % 11 == 1)
		apply_color_map(dusk);
	else if (col_iter % 11 == 2)
		apply_color_map(kryptonite);
	else if (col_iter % 11 == 3)
		apply_color_map(red_blue);
	else if (col_iter % 11 == 4)
		apply_color_map(fire);
	else if (col_iter % 11 == 5)
		apply_color_map(ice);
	else if (col_iter % 11 == 6)
		apply_color_map(seashore);
	else if (col_iter % 11 == 7)
		apply_color_map(kryptonite_center);
	else if (col_iter % 11 == 8)
		apply_color_map(seashore_center);
	else if (col_iter % 11 == 9)
		apply_color_map(fire_center);
	else if (col_iter % 11 == 10)
		apply_color_map(dawn_center);
	draw_map();
}

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

void set_copy(void)
{
	int i;

	i = 0;
	while (i < len * max_strs)
	{
		c_pnts[i].x = pnts[i].x;
		c_pnts[i].y = pnts[i].y;
		c_pnts[i].z = pnts[i].z;
		i++;
	}
}

void reset_map(void)
{
	int i;

	i = 0;
	while (i < len * max_strs)
	{
		pnts[i].x = c_pnts[i].x;
		pnts[i].y = c_pnts[i].y;
		pnts[i].z = c_pnts[i].z;
		i++;
	}
	translation_h((WIDTH / 2) - (len / 2));
	translation_v((HEIGHT / 2) - (max_strs / 2));
	scale((WIDTH * 3)/ (len * 5));	
}

void get_map(char *file_name)
{
	int fd;
	int j;
	int p = 0;
	char **map;
	char *temp;
	char **tmp;
	char *str;
	int i;
	int col;
	int next_space;
	char *num;
	

	fd = open(file_name, O_RDONLY);
	j = 0;
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
		j++;
	}
	close(fd);
	max_strs = j;
	map = ft_strsplit(temp, ',');
	len = ft_strlen(temp)/ max_strs + 1;
	j = 0;
	while (tmp[j] != NULL)
		j++;
	ft_strdel(tmp);
	ft_strdel(&temp);
	len = j;
	j = 0;
	pnts = (t_vec*)malloc(sizeof(t_vec) * (len * max_strs));
	while (j  < max_strs)
	{
		i = 0;
		while (i  < len)
		{
			map[j] = ft_strtrim(map[j]);
			if ((num  = ft_strchr(map[j], ' ')) != NULL)
			{
				if (num[1] == ' ')
					num++;
				num[0] = '\0';
				col = ft_atoi(map[j]);
				map[j] = ft_strdup(num + 1);
				pnts[p].x = i;
				pnts[p].y = j;
				pnts[p].z = col;
				// pnts[p].color =  colors[abs(col) % 24];
				
			}
			else
			{
				col = ft_atoi(map[j]);
				pnts[p].x = i;
				pnts[p].y = j;
				pnts[p].z = col;
				// pnts[p].color =  colors[abs(col) % 24];
			
			}
			if (p == 0)
			{
				c_max = pnts[p].z;
				c_min = pnts[p].z;
			}
			else
			{
				c_max = pnts[p].z > c_max ? pnts[p].z : c_max;
				c_min = pnts[p].z < c_min ? pnts[p].z : c_min;
				// printf("Max = %f  Min = %f\n", c_max, c_min);
			}
			p++;
			i++;
		}
		j++;
	}
	c_pnts = (t_vec*)malloc(sizeof(t_vec) * len * max_strs);
	set_copy();
	translation_h((WIDTH / 2) - (len / 2));
	translation_v((HEIGHT / 2) - (max_strs / 2));
	scale((WIDTH * 3)/ (len * 5));
}

void load_next_map(void)
{
	ft_bzero((void *)keys, 1024);
	key_len = 0;
	ft_memdel((void **)&pnts);
	ft_memdel((void **)&c_pnts);
	file_num++;
	ft_printf("Before Loading new map\n");
	get_map(files[file_num % max_files]);
	mlx_clear_window(mlx, win);
	set_color_map(0);
}
int my_key_pressed(int keycode, void *mlx)
{
	ft_printf("My key pressed = %d\n", keycode);
	if (keycode == 0)
		flags |= rot_x;
	else if (keycode == 1)
		flags |= rot_x_neg | sign;
	else if (keycode == 2)
		flags |= rot_y;
	else if (keycode == 3)
		flags |= rot_y_neg | sign;
	else if (keycode == 6)
		flags |= rot_z;
	else if (keycode == 7)
		flags |= rot_z | sign;
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
	printf("Flags = %u\n", flags );
	return (0);
}

int my_loop_hook(void *mlx)
{
	ft_printf("Hook flags = %u\n", flags);
	if (flags & rot_x_neg)
		rotation_x(-0.125);
	if (flags & rot_y_neg)
		rotation_y(-0.125);
	if (flags & rot_x)
		rotation_x(0.125);
	if (flags & rot_y)
		rotation_y(0.125);
	if (flags & sign)
	{
		if (flags & rot_z)
			rotation_z(-0.125);
		else if (flags & scl)
			scale(0.8);
		else if (flags & tran_h)
			translation_h(-10.0);
		else if (flags & tran_v)
			translation_v(-10.0);
	}
	else
	{
		if (flags & rot_z)
			rotation_z(0.125);
		else if (flags & scl)
			scale(1.25);
		else if (flags & tran_h)
			translation_h(10.0);
		else if (flags & tran_v)
			translation_v(10.0);
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

int my_mouse_motion(int i , int j , void *mlx)
{
	//ft_printf("Motion Button = %d X = %d Y = %d\n", button, i, j);
	if (flags & mous && !((j - 590) - (i - 1050) >= -40 
		&& (j - 590) + (i - 1050) >= 40 && 
		(j - 750) + (i - 1050) <= 80 && (j - 750) <= (i - 1050)))
		flags = 0;
	return (0);
}

int my_mouse_released(int button, int i, int j, void *mlx)
{
	// ft_printf("Release Button = %d  X = %d  Y  = %d\n", button, i, j);	
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
		flags |= rot_y_neg | sign | mous;
	else if ((j - 750) + (i - 1050) <= 80 && (j - 750) <= (i - 1050) && (j - 750) >= 0)
		flags |= rot_x_neg | sign | mous;
	else if ((j - 650) + (i - 990) >= 40 && (j - 650) - (i - 990) <= 40 && (i - 990) <= 40)
		flags |= rot_y | mous;
	else if (button == 5  && iter < 10)
	{
		iter++;
		draw_legend();
	}
	else if (button == 7 && iter > 0)
	{
		iter--;
		draw_legend();
	}
	else if (button == 1 && j >= 590 && j <= 750 && i <= 1150 && i >= 990 && 
		(j - 590) - (i - 1050) >= -40 && (j - 590) + (i - 1050) >= 40 && 
		(j - 750) + (i - 1050) <= 80 && (j - 750) <= (i - 1050))
		set_color_map(1);
	else if (button == 2 && j >= 590 && j <= 750 && i <= 1150 && i >= 990 && 
		(j - 590) - (i - 1050) >= -40 && (j - 590) + (i - 1050) >= 40 && 
		(j - 750) + (i - 1050) <= 80 && (j - 750) <= (i - 1050))
		load_next_map();
	return (0);
}


int main(int argc, char **argv)
{
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "mlx_42");
	mlx_do_key_autorepeatoff(mlx);
	init_colors();
	keys = (unsigned int *)malloc(sizeof(unsigned int) * 1024);
	if (argc >= 2)
	{
		// ft_printf("Calling draw map\n");
		int i = 1;
		while (argv[i])
		{
			max_files++;
			i++;
		}
		ft_printf("Max files = %d\n", max_files);
		files = (char **)malloc(sizeof(char*) * max_files);
		i = 1;
		while (argv[i])
		{
			files[i - 1] = ft_strdup(argv[i]);
			i++;
		}
		// file = argv[1];
		get_map(files[file_num]);
		set_color_map(0);
	}
	//mlx_put_image_to_window(mlx, win, img, 0, 0);
	// mlx_loop_hook(mlx, my_loop_hook, win);
	// mlx_key_pressed_hook(win, my_key_pressed, mlx);
	mlx_key_hook(win, my_key_funct, mlx);
	mlx_hook(win, 2, 0, my_key_pressed, mlx);
	mlx_hook(win, 5, 0, my_mouse_released, mlx);
	mlx_hook(win, 6, 0, my_mouse_motion, mlx);
	mlx_mouse_hook(win, my_mouse_function, mlx);
	mlx_loop_hook(mlx, my_loop_hook, win);
	mlx_loop(mlx);
	
}
