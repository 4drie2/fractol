/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:25:46 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/02 09:06:13 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"

static unsigned int	*_std(void)
{
	static unsigned int	color[] = {
		0x000764FF,
		0x206BCBFF,
		0xEDFFFFFF,
		0xFFAA00FF,
		0x000000FF,
		0
	};

	return (color);
}

static unsigned int	*_rainbow(void)
{
	static unsigned int	color[] = {
		0xFF0000FF,
		0xFFFF00FF,
		0x00FF00FF,
		0x00FFFFFF,
		0x0000FFFF,
		0xFF00FFFF,
		0
	};

	return (color);
}

static unsigned int	*neon_blue(void)
{
	static unsigned int	color[] = {
		0x0F00FFFF,
		0x0F006FFF,
		0x00FFF0FF,
		0x5F00FFFF,
		0
	};

	return (color);
}

void	get_color(t_color *color)
{
	static unsigned int	*(*f_array[])(void) = {_std, _rainbow,
		neon_blue};
	uint32_t			*temp;
	uint16_t			palette_size;
	static uint8_t		index = 0;

	temp = f_array[index]();
	color->palette = temp;
	palette_size = 0;
	while (temp[palette_size])
		palette_size++;
	color->palette_size = palette_size;
	index = (index + 1) % 3;
}

uint32_t	linear_interpolate(uint32_t color1, uint32_t color2, double t)
{
	static t_rgb	color;

	color.r1 = (color1 >> 24) & 0xFF;
	color.g1 = (color1 >> 16) & 0xFF;
	color.b1 = (color1 >> 8) & 0xFF;
	color.r2 = (color2 >> 24) & 0xFF;
	color.g2 = (color2 >> 16) & 0xFF;
	color.b2 = (color2 >> 8) & 0xFF;
	return ((uint8_t)(color.r1 + t * (color.r2 - color.r1)) << 24
		| (uint8_t)(color.g1 + t * (color.g2 - color.g1)) << 16
		| (uint8_t)(color.b1 + t * (color.b2 - color.b1)) << 8
		| 0xFF);
}
