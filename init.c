/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:04:50 by abidaux           #+#    #+#             */
/*   Updated: 2025/03/14 00:46:39 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void)
{
	perror("malloc error x_x");
	exit(EXIT_FAILURE);
}

static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iteration_definition = 42;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1;
}

static void	event_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_windows,
		KeyPress,
		KeyPressMask,
		key_handler,
		fractal);
	mlx_hook(fractal->mlx_windows,
		ButtonPress,
		ButtonPressMask,
		mouse_handler,
		fractal);
	mlx_hook(fractal->mlx_windows,
		DestroyNotify,
		StructureNotifyMask,
		close_handler,
		fractal);
	mlx_hook(fractal->mlx_windows,
		MotionNotify,
		PointerMotionMask,
		julia_track,
		fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connexion = mlx_init();
	if (!fractal->mlx_connexion)
		malloc_error();
	fractal->mlx_windows = mlx_new_window(fractal->mlx_connexion,
			WIDH, HEIGHT, fractal->name);
	if (!fractal->mlx_windows)
	{
		mlx_destroy_display(fractal->mlx_connexion);
		free(fractal->mlx_connexion);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connexion,
			WIDH, HEIGHT);
	if (!fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_connexion, fractal->mlx_windows);
		mlx_destroy_display(fractal->mlx_connexion);
		free(fractal->mlx_connexion);
		malloc_error();
	}
	fractal->img.pixel_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	event_init(fractal);
	data_init(fractal);
}
