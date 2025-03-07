/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:20:33 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/02 12:20:59 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx_resize_image(mlx->image, width, height);
	mlx->fractal(mlx);
}

void	close_hook(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx_close_window(mlx->mlx);
}
