/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:58:08 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/04 09:00:14 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline double	_tricorn(t_data data)
{
	double	iteration;
	double	y2;
	double	x2;
	double	log_zn;
	double	nu;

	iteration = 0.0;
	y2 = 0;
	x2 = 0;
	while (x2 + y2 < (1 << 16) && iteration < MAXITERATION)
	{
		data.zy = -2 * data.zx * data.zy + data.cy;
		data.zx = x2 - y2 + data.cx;
		x2 = data.zx * data.zx;
		y2 = data.zy * data.zy;
		iteration++;
	}
	if (iteration < MAXITERATION)
	{
		log_zn = log(data.zx * data.zx + data.zy * data.zy) / 2;
		nu = log(log_zn / log(2)) / log(2);
		iteration = iteration + 1 - nu;
	}
	return (iteration);
}

static void	_set_data(t_mlx *mlx)
{
	mlx->data.zoom_x = mlx->image->width
		/ ((mlx->data.x2 - mlx->data.x1) * mlx->data.zoom);
	mlx->data.zoom_y = mlx->image->height
		/ ((mlx->data.y2 - mlx->data.y1) * mlx->data.zoom);
}

static void	_draw_tricorn(t_mlx *mlx)
{
	double		count;
	uint32_t	x;
	uint32_t	y;

	_set_data(mlx);
	y = 0;
	while (y < mlx->image->height)
	{
		x = 0;
		while (x < mlx->image->width)
		{
			mlx->data.cx = x / mlx->data.zoom_x + mlx->data.x1;
			mlx->data.cy = y / mlx->data.zoom_y + mlx->data.y1;
			mlx->data.zx = 0;
			mlx->data.zy = 0;
			count = _tricorn(mlx->data);
			mlx->color.colorator(count, x, y, mlx);
			x++;
		}
		y++;
	}
}

void	tricorn(t_mlx *mlx)
{
	static uint8_t	is_setup = 0;

	if (!is_setup)
	{
		mlx->data.zoom = 1.0;
		mlx->data.x1 = -2.05;
		mlx->data.x2 = 1;
		mlx->data.y1 = -1.5;
		mlx->data.y2 = 1.5;
		mlx->data.delta_x = mlx->data.x2 - mlx->data.x1;
		mlx->data.delta_y = mlx->data.y2 - mlx->data.y1;
		is_setup = 1;
	}
	_draw_tricorn(mlx);
}
