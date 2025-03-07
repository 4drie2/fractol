/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:31:35 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/06 08:57:00 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mouve_hook(t_mlx *mlx)
{
	double	move_x;
	double	move_y;
	int		multi;

	move_x = 0;
	move_y = 0;
	multi = 1;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
		move_x = -0.2 * mlx->data.zoom;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
		move_x = 0.2 * mlx->data.zoom;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_UP))
		move_y = -0.2 * mlx->data.zoom;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
		move_y = 0.2 * mlx->data.zoom;
	mlx->data.x1 += move_x;
	mlx->data.x2 += move_x;
	mlx->data.y1 += move_y;
	mlx->data.y2 += move_y;
	if (move_x != 0 || move_y != 0)
		mlx->fractal(mlx);
}

static void	zoom_hook(t_mlx *mlx)
{
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_F))
	{
		mlx->data.y1 += mlx->data.delta_y * mlx->data.zoom * 0.1;
		mlx->data.y2 += mlx->data.delta_y * mlx->data.zoom * 0.1;
		mlx->data.x1 += mlx->data.delta_x * mlx->data.zoom * 0.1;
		mlx->data.x2 += mlx->data.delta_x * mlx->data.zoom * 0.1;
		mlx->data.zoom *= 0.80;
		mlx->fractal(mlx);
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_G))
	{
		mlx->data.y1 -= mlx->data.delta_y * mlx->data.zoom * 0.1;
		mlx->data.y2 -= mlx->data.delta_y * mlx->data.zoom * 0.1;
		mlx->data.x1 -= mlx->data.delta_x * mlx->data.zoom * 0.1;
		mlx->data.x2 -= mlx->data.delta_x * mlx->data.zoom * 0.1;
		mlx->data.zoom *= 1.20;
		mlx->fractal(mlx);
	}
}

static void	_key_hook(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->mlx);
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_KP_7))
	{
		get_colorator(mlx);
		mlx->fractal(mlx);
	}
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_KP_9))
	{
		get_color(&mlx->color);
		mlx->fractal(mlx);
	}
	mouve_hook(mlx);
	zoom_hook(mlx);
}

bool	init_hook(t_mlx *mlx)
{
	char	result;

	result = 0;
	result += mlx_loop_hook(mlx->mlx, _key_hook, mlx);
	result += mlx_loop_hook(mlx->mlx, julia_mouse_track, mlx);
	if (result != 2)
		return (EXIT_FAILURE);
	mlx_close_hook(mlx->mlx, close_hook, mlx);
	mlx_resize_hook(mlx->mlx, resize_hook, mlx);
	mlx_scroll_hook(mlx->mlx, scroll_hook, mlx);
	return (EXIT_SUCCESS);
}
