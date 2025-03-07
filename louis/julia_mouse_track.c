/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_mouse_track.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:13:45 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/02 10:31:28 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia_mouse_track(void *param)
{
	t_mlx		*mlx;
	int32_t		mx;
	int32_t		my;
	static bool	mouse_tracking = false;

	mlx = param;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_T))
		mouse_tracking = true;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_Y))
		mouse_tracking = false;
	if (mouse_tracking == false)
		return ;
	mlx_get_mouse_pos(mlx->mlx, &mx, &my);
	if (mx < 0 || my < 0 || mx > mlx->mlx->width || my > mlx->mlx->height)
		return ;
	mlx->julia.cx = (mx - mlx->mlx->height / 2)
		* (mlx->data.x1 * 2 / mlx->mlx->width);
	mlx->julia.cy = (my - mlx->mlx->width / 2)
		* (mlx->data.y1 * 2 / mlx->mlx->height);
	mlx->fractal(mlx);
}
