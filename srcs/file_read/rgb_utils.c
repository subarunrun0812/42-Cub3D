/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:15:30 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 18:38:39 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// rgbの引数が数値であるかチェックする
int	check_num(char *num_str)
{
	int	i;

	i = 0;
	while (num_str[i] != '\0')
	{
		if (('0' <= num_str[i] && num_str[i] <= '9') || (num_str[i] == '-'
				|| num_str[i] != '+'))
			i++;
		else
			return (-1);
	}
	return (0);
}

void	init_rgb_values(t_rgb *rgb)
{
	rgb->red = -1;
	rgb->green = -1;
	rgb->blue = -1;
}
