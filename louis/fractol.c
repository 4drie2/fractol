/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:01:52 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/02 11:16:12 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	static t_mlx	mlx;

	if (!get_para(argc, argv, &mlx))
		return (ft_printf("%s\n", ERROR_PARA), EXIT_SUCCESS);
	if (init_mlx_window(&mlx) == EXIT_FAILURE)
		return (mlx_terminate(mlx.mlx), EXIT_FAILURE);
	get_color(&mlx.color);
	get_colorator(&mlx);
	mlx.fractal(&mlx);
	if (init_hook(&mlx) == EXIT_FAILURE)
		return (mlx_terminate(mlx.mlx), 0);
	mlx_loop(mlx.mlx);
	mlx_terminate(mlx.mlx);
	return (EXIT_SUCCESS);
}
