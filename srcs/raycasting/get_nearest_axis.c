/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nearest_axis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 11:37:16 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_hit_wall(char **map, t_ray *ray)
{
	if ('1' == map[ray->x_map][ray->y_map])
	{
		return (true);
	}
	return (false);
}

static int	calculate_step_x_direction(t_ray *ray, t_vars *vars)
{
	if (ray->x_dir < 0)
	{
		ray->x_side_dist = (vars->x_pos - ray->x_map)
			* ray->x_delta_dist;
		return (-1);
	}
	ray->x_side_dist = (ray->x_map + 1.0
			- vars->x_pos) * ray->x_delta_dist;
	return (1);
}

static int	calculate_step_y_direction(t_ray *ray, t_vars *vars)
{
	if (ray->y_dir < 0)
	{
		ray->y_side_dist = (vars->y_pos - ray->y_map)
			* ray->y_delta_dist;
		return (-1);
	}
	ray->y_side_dist = (ray->y_map + 1.0
			- vars->y_pos) * ray->y_delta_dist;
	return (1);
}

// perform DDA
int	get_nearest_axis(t_ray *ray, t_info *info)
{
	int	step_x;
	int	step_y;
	int	axis;

	step_x = calculate_step_x_direction(ray, &info->vars);
	step_y = calculate_step_y_direction(ray, &info->vars);
	while (1)
	{
		if (ray->x_side_dist < ray->y_side_dist)
		{
			ray->x_side_dist += ray->x_delta_dist;
			ray->x_map += step_x;
			axis = X_AXIS;
		}
		else
		{
			ray->y_side_dist += ray->y_delta_dist;
			ray->y_map += step_y;
			axis = Y_AXIS;
		}
		if (is_hit_wall(info->map.map_data, ray))
			break ;
	}
	return (axis);
}
