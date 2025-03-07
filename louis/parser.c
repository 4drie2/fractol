/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:44:53 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/02 12:58:02 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	_parse_para(char *str, t_mlx *mlx)
{
	char		**para;

	para = ft_split(str, ',');
	if (split_size(para) != 2)
		return (free_split(para), 0);
	if (!is_double_str(para[0]))
		return (free_split(para), 0);
	mlx->julia.cx = ft_atof(para[0]);
	if (!is_double_str(para[1]))
		return (free_split(para), 0);
	mlx->julia.cy = ft_atof(para[1]);
	return (free_split(para), 1);
}

static int	_get_julia_param(t_parsing *param, t_mlx *mlx)
{
	mlx->julia.cx = -0.77146;
	mlx->julia.cy = -0.10119;
	if (param->argc < 3)
		return (1);
	else
	{
		param->index++;
		if (!ft_strchr(param->argv[param->index], ','))
			return (0);
		if (!_parse_para(param->argv[param->index], mlx))
			return (0);
		return (1);
	}
}

static int	_get_fractal(t_parsing *param, t_mlx *mlx)
{
	mlx->fractal = NULL;
	if (!ft_strcmp(param->argv[param->index], "-m"))
		mlx->fractal = &mandelbrot;
	else if (!ft_strcmp(param->argv[param->index], "-t"))
		mlx->fractal = &tricorn;
	else if (!ft_strcmp(param->argv[param->index], "-b"))
		mlx->fractal = &burning_ship;
	else if (!ft_strcmp(param->argv[param->index], "-j"))
	{
		mlx->fractal = &julia;
		if (!_get_julia_param(param, mlx))
			return (0);
	}
	if (mlx->fractal == NULL)
		return (0);
	return (1);
}

int	get_para(int argc, char **argv, t_mlx *mlx)
{
	static t_parsing	param;

	param.argv = argv;
	param.argc = argc;
	param.index = 1;
	mlx->color.palette = NULL;
	if (argc < 2 || argc > 3)
		return (0);
	if (!_get_fractal(&param, mlx))
		return (0);
	return (1);
}
