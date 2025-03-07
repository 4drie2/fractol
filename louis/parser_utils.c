/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:45:18 by lchauvet          #+#    #+#             */
/*   Updated: 2024/12/06 12:48:33 by lchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	is_double_str(char *str)
{
	uint16_t	index;
	bool		dot;

	index = 0;
	dot = 0;
	if (str[index] == '-' || str[index] == '+')
		str++;
	while (str[index])
	{
		if ((str[index] < '0' || str[index] > '9')
			&& (str[index] != '.' && dot != 1))
			return (0);
		if (str[index] == '.')
			dot = 1;
		index++;
	}
	return (1);
}

uint16_t	split_size(char **array)
{
	uint16_t	count;

	if (!array || !*array)
		return (0);
	count = 0;
	while (array[count])
		count++;
	return (count);
}

void	free_split(char **array)
{
	uint16_t	index;

	if (!array || !*array)
		return ;
	index = 0;
	while (array[index])
		free(array[index++]);
	free(array);
}
