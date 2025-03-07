/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:56:38 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/06 08:56:37 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#define WIDTH 500
#define HEIGHT 500

static int	_init_image(t_mlx *mlx)
{
	mlx->image = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->image || (mlx_image_to_window(mlx->mlx, mlx->image, 0, 0) < 0))
		return (EXIT_FAILURE);
	if (mlx_image_to_window(mlx->mlx, mlx->image, 0, 0) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_mlx_window(t_mlx *mlx)
{
	if (!mlx)
		return (EXIT_FAILURE);
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "fract’ol", true);
	if (!mlx->mlx)
		return (EXIT_FAILURE);
	if (_init_image(mlx))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
