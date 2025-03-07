/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:58:08 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/04 09:00:10 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline double	_julia(t_data data)
{
	double	iteration;
	double	temp;
	double	log_zn;
	double	nu;

	iteration = 0.0;
	while ((data.zx * data.zx + data.zy * data.zy) <= (1 << 16)
		&& iteration < MAXITERATION)
	{
		temp = data.zx * data.zx - data.zy * data.zy + data.cx;
		data.zy = 2 * data.zx * data.zy + data.cy;
		data.zx = temp;
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

static void	_draw_julia(t_mlx *mlx)
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
			mlx->data.cx = mlx->julia.cx;
			mlx->data.cy = mlx->julia.cy;
			mlx->data.zx = x / mlx->data.zoom_x + mlx->data.x1;
			mlx->data.zy = y / mlx->data.zoom_y + mlx->data.y1;
			count = _julia(mlx->data);
			mlx->color.colorator(count, x, y, mlx);
			x++;
		}
		y++;
	}
}

void	julia(t_mlx *mlx)
{
	static bool	is_setup = false;

	if (is_setup == false)
	{
		mlx->data.zoom = 1.0;
		mlx->data.x1 = -2;
		mlx->data.x2 = 2;
		mlx->data.y1 = -2;
		mlx->data.y2 = 2;
		mlx->data.delta_x = mlx->data.x2 - mlx->data.x1;
		mlx->data.delta_y = mlx->data.y2 - mlx->data.y1;
		is_setup = true;
	}
	_draw_julia(mlx);
}
//-0.77146 -0.10119
