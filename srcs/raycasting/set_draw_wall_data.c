/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_draw_wall_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/10 13:36:07 by susasaki         ###   ########.fr       */
/*   Updated: 2023/07/06 17:55:01 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_wall_distance(t_ray *ray, int side)
{
	if (side == X_AXIS)
	{
		return (ray->x_side_dist - ray->x_delta_dist);
	}
	return (ray->y_side_dist - ray->y_delta_dist);
}

static int	get_draw_start_y_coordinate(int line_height)
{
	int	start;

	start = (-line_height / 2) + (WIN_HEIGHT / 2);
	if (start < 0)
	{
		return (0);
	}
	return (start);
}

static int	get_draw_end_y_coordinate(int line_height)
{
	int	end;

	end = (line_height / 2) + (WIN_HEIGHT / 2);
	if (WIN_HEIGHT <= end)
	{
		return (WIN_HEIGHT - 1);
	}
	return (end);
}

void	set_draw_wall_data(t_draw_wall *wall, t_ray *ray, t_info *info)
{
	wall->side = get_nearest_axis(ray, info);
	wall->wall_dist
		= get_wall_distance(ray, wall->side);
	wall->line_height = (int)(WIN_HEIGHT
			/ wall->wall_dist);
	wall->start_y = get_draw_start_y_coordinate(wall->line_height);
	wall->end_y = get_draw_end_y_coordinate(wall->line_height);
}
