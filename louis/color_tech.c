/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tech.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:16:02 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/02 10:22:32 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline uint32_t	_cw(uint32_t color1, uint32_t color2, double segment)
{
	static t_rgb	color;

	color.r1 = (color1 >> 24) & 0xFF;
	color.g1 = (color1 >> 16) & 0xFF;
	color.b1 = (color1 >> 8) & 0xFF;
	color.r2 = (color2 >> 24) & 0xFF;
	color.g2 = (color2 >> 16) & 0xFF;
	color.b2 = (color2 >> 8) & 0xFF;
	return ((uint8_t)((1 - segment) * color.r1 + segment * color.r2) << 24
		| (uint8_t)((1 - segment) * color.g1 + segment * color.g2) << 16
		| (uint8_t)((1 - segment) * color.b1 + segment * color.b2) << 8 | 0xFF);
}

void	p_base(double count, uint32_t x, uint32_t y, t_mlx *mlx)
{
	uint8_t	color;

	if (count == MAXITERATION)
		mlx_put_pixel(mlx->image, x, y, 0x000000FF);
	else
	{
		color = (count * 255) / 100;
		mlx_put_pixel(mlx->image, x, y,
			color << 24 | color << 16 | 0 << 8 | 0xFF);
	}
}

void	p_repeat(double iter, uint32_t x, uint32_t y, t_mlx *mlx)
{
	uint32_t	color;
	double		fractional;
	size_t		index;

	if (iter == MAXITERATION)
		mlx_put_pixel(mlx->image, x, y, 0x000000FF);
	else
	{
		fractional = iter - floor(iter);
		index = (size_t)floor(iter) % mlx->color.palette_size;
		color = linear_interpolate(mlx->color.palette[index],
				mlx->color.palette[(index + 1) % mlx->color.palette_size],
				fractional);
		mlx_put_pixel(mlx->image, x, y, color);
	}
}

void	p_fluent(double iter, uint32_t x, uint32_t y, t_mlx *mlx)
{
	double		normalized;
	uint32_t	color1;
	uint32_t	color2;
	uint32_t	segment_index;

	if (iter == MAXITERATION)
		mlx_put_pixel(mlx->image, x, y, 0x000000FF);
	else
	{
		normalized = iter / MAXITERATION;
		segment_index = (uint32_t)(normalized * mlx->color.palette_size);
		if (segment_index >= mlx->color.palette_size)
			segment_index = mlx->color.palette_size - 1;
		color1 = mlx->color.palette[segment_index];
		color2 = mlx->color.palette[(segment_index + 1)
			% mlx->color.palette_size];
		mlx_put_pixel(mlx->image, x, y, _cw(color1, color2,
				fmod(normalized * mlx->color.palette_size, 1.0)));
	}
}

void	get_colorator(t_mlx *mlx)
{
	static void		(*f_a[])(double iter, uint32_t x, uint32_t y, t_mlx *mlx)
		= {p_fluent, p_repeat, p_base};
	static uint8_t	index = 0;

	mlx->color.colorator = f_a[index];
	index = (index + 1) % 3;
}
