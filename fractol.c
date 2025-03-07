/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidaux <abidaux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:51:29 by abidaux           #+#    #+#             */
/*   Updated: 2025/03/07 18:51:57 by abidaux          ###   ########.fr       */
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
