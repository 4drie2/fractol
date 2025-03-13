/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:05:39 by abidaux           #+#    #+#             */
/*   Updated: 2025/03/14 00:36:14 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define ERROR_MESSAGE_PART1 "Please enter \n\t\"./fractol mandelbrot\" or \n\""
#define ERROR_MESSAGE_PART2 "\t./fractol julia <value_1> <value_2>\"\n"

#define WIDH	800
#define HEIGHT	800

#define BLACK	0x000000
#define WHITE	0xFFFFFF
#define RED		0xFF0000
#define GREEN	0x00FF00
#define BLUE	0x0000FF

// LSD COLOR
#define MAGENTA_BURST		0xFF00FF
#define LIME_SHOCK			0x39FF14
#define NEON_ORANGE			0xFF5F1F
#define PSYCHEDELIC_PURPLE	0xB026FF
#define AQUA_DREAM			0x0AFFFF
#define HOT_PINK			0xFF10F0
#define ELECTRIC_BLUE		0x0CEFFF
#define LAVA_RED			0xFF1700

typedef struct s_complex
{
	double	x;
	double	y;
}				t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_connexion;
	void	*mlx_windows;
	t_img	img;
	double	escape_value;
	int		iteration_definition;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;

int			ft_strncmp(char *s1, char *s2, int n);
void		putstr_fd(char *s, int fd);
double		atodbl(char *s);
void		fractal_init(t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
double		map(double unscaled_num, double new_min,
				double new_max, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, t_fractal *fractal);
int			julia_track(int x, int y, t_fractal *fractal);
