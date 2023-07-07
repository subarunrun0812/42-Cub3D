/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color_floor_and_ceil.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 13:50:58 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_color_floor_and_ceil(t_data *data, unsigned int floor_col
		, unsigned int ceil_col)
{
	int	x_axis;
	int	y_axis_floor[2];
	int	y_axis_ceil[2];

	x_axis = 0;
	y_axis_floor[0] = 0;
	y_axis_floor[1] = (WIN_HEIGHT / 2) - 1;
	y_axis_ceil[0] = y_axis_floor[1];
	y_axis_ceil[1] = WIN_HEIGHT - 1;
	while (x_axis < WIN_WIDTH)
	{
		my_mlx_pixel_put_line(data, x_axis, y_axis_floor, floor_col);
		my_mlx_pixel_put_line(data, x_axis, y_axis_ceil, ceil_col);
		x_axis += 1;
	}
}
