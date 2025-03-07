/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:53:29 by lchauvet          #+#    #+#             */
/*   Updated: 2025/03/06 22:04:49 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "libft/libft.h"
#include "minilibx/mlx42.h"

#define MAXITERATION 250

#define ERROR_PARA "./fractol [fratal] (julia option)\n\
[fractal]\n\
-m mandelbrot\n\
-j julia\n\
-b burning_ship\n\
-t tricorn\n\
\n(julia option)\n\
ex: '-2.23,1.5'\n"

typedef struct s_parsing
{
	char	**argv;
	int		argc;
	int		index;
}			t_parsing;

typedef struct s_data
{
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	double	zoom;
	double	zoom_x;
	double	zoom_y;
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	delta_x;
	double	delta_y;
}			t_data;

typedef struct s_julia
{
	double	cx;
	double	cy;
}			t_julia;

typedef struct s_mlx	t_mlx;

typedef struct s_color
{
	void		(*colorator)(double iter, uint32_t x, uint32_t y, t_mlx *mlx);
	uint32_t	*palette;
	uint16_t	palette_size;
}			t_color;

struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	void		(*fractal)(struct s_mlx *mlx);
	t_julia		julia;
	t_data		data;
	t_color		color;
};

typedef struct s_rgb
{
	uint8_t		r1;
	uint8_t		g1;
	uint8_t		b1;
	uint8_t		r2;
	uint8_t		g2;
	uint8_t		b2;
}			t_rgb;

// fractal
void		mandelbrot(t_mlx *mlx);
void		julia(t_mlx *mlx);
void		multi_brot(t_mlx *mlx);
void		burning_ship(t_mlx *mlx);
void		tricorn(t_mlx *mlx);

void		julia_mouse_track(void *param);

//color
void		get_color(t_color *color);
uint32_t	linear_interpolate(uint32_t color1, uint32_t color2, double t);
inline void		p_sharp(double iter, uint32_t x, uint32_t y, t_mlx *mlx);
void		p_base(double count, uint32_t x, uint32_t y, t_mlx *mlx);
void		p_fluent(double iter, uint32_t x, uint32_t y, t_mlx *mlx);
void		get_colorator(t_mlx *mlx);

// mlx init
int			get_para(int argc, char **argv, t_mlx *mlx);
int			init_mlx_window(t_mlx *mlx);
bool		init_hook(t_mlx *mlx);

// parser utils
void		free_split(char **array);
uint16_t	split_size(char **array);
bool		is_double_str(char *str);

// end mlx
void		my_mlx_end(t_mlx *mlx);

//hook
void		scroll_hook(double xdelta, double ydelta, void *param);
void		resize_hook(int32_t width, int32_t height, void *param);
void		close_hook(void *param);
