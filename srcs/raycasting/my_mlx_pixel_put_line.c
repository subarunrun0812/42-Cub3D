/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 13:47:44 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put_line(t_data *data, int x_axis, int y_axis[2],
		unsigned int color)
{
	int				y;
	unsigned int	*dst;

	y = y_axis[0];
	while (y <= y_axis[1])
	{
		dst = data->addr + (y * WIN_WIDTH + x_axis);
		*dst = color;
		y += 1;
	}
}
