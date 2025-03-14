/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:51:29 by abidaux           #+#    #+#             */
/*   Updated: 2025/03/14 00:39:09 by abidaux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
to compile :
Download minilibx-linux ;
gcc *.c -I ~/my_libs/minilibx/ -L ~/my_libs/minilibx/
 -lmlx -lX11 -lXext -lbsd -Lminilibx-linux
*/

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
		|| (ac == 4 && !ft_strncmp(av[1], "julia", 5)))
	{
		fractal.name = av[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(av[2]);
			fractal.julia_y = atodbl(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connexion);
	}
	else
	{
		putstr_fd(ERROR_MESSAGE_PART1, STDERR_FILENO);
		putstr_fd(ERROR_MESSAGE_PART2, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
