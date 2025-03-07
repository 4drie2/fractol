/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:50:57 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/04 09:08:28 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	_mouse_mouve(t_mlx *mlx, char pos, double mx, double my)
{
	int8_t	side;

	if (pos > 0)
		side = 1;
	else
		side = -1;
	mlx->data.x1 += side * (mlx->data.delta_x * ((2 * ((double)mx
						/ mlx->image->width)) - 1)) * mlx->data.zoom * 0.1;
	mlx->data.x2 += side * (mlx->data.delta_x * ((2 * ((double)mx
						/ mlx->image->width)) - 1)) * mlx->data.zoom * 0.1;
	mlx->data.y1 += side * (mlx->data.delta_y * ((2 * ((double)my
						/ mlx->image->height)) - 1)) * mlx->data.zoom * 0.1;
	mlx->data.y2 += side * (mlx->data.delta_y * ((2 * ((double)my
						/ mlx->image->height)) - 1)) * mlx->data.zoom * 0.1;
}

static void	_zoom(t_mlx *mlx, char pos)
{
	int8_t	side;

	if (pos > 0)
		side = 1;
	else
		side = -1;
	mlx->data.x1 += side * mlx->data.delta_x * mlx->data.zoom * 0.1;
	mlx->data.x2 += side * mlx->data.delta_x * mlx->data.zoom * 0.1;
	mlx->data.y1 += side * mlx->data.delta_y * mlx->data.zoom * 0.1;
	mlx->data.y2 += side * mlx->data.delta_y * mlx->data.zoom * 0.1;
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_mlx	*mlx;
	int32_t	mx;
	int32_t	my;

	mlx = param;
	mlx_get_mouse_pos(mlx->mlx, &mx, &my);
	_mouse_mouve(mlx, ydelta, mx, my);
	_zoom(mlx, ydelta);
	if (ydelta > 0)
		mlx->data.zoom *= 0.80;
	else if (ydelta < 0)
		mlx->data.zoom *= 1.20;
	mlx->fractal(mlx);
	(void)xdelta;
}
