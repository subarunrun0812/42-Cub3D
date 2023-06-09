/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_nearest_axis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:30:47 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/24 15:05:37 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

static bool	is_hit_wall(t_ray *ray,t_info *info)
{
	// 壁に衝突した場合にtrueを返す
	// printf("world_map = %d\n",world_map[ray->current_x_in_map][ray->current_y_in_map]);
	// printf("map_data = %d\n",g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map]);
	if ('0' < info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] &&
	info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] < '9')
	{
		return (true);
	}
	return (false);
}

static int	calculate_step_x_direction(t_ray *ray, t_vars *vars)
{
	if(ray->x_direction < 0)
	{
		ray->x_side_distance = (vars->x_position_vector - ray->current_x_in_map) * ray->x_delta_distance;
		return (-1);
	}
	ray->x_side_distance = (ray->current_x_in_map + 1.0 - vars->x_position_vector) * ray->x_delta_distance;
	return (1);
}

static int	calculate_step_y_direction(t_ray *ray, t_vars *vars)
{
	if(ray->y_direction < 0)
	{
		ray->y_side_distance = (vars->y_position_vector - ray->current_y_in_map) * ray->y_delta_distance;
		return (-1);
	}
	ray->y_side_distance = (ray->current_y_in_map + 1.0 - vars->y_position_vector) * ray->y_delta_distance;
	return (1);
}

//DDAアルゴリズムで3次元空間内のオブジェクトが衝突するまでrayを飛ばす
bool	calculate_nearest_axis(t_ray *ray, t_vars *vars,t_info *info)
{
	int		step_x;
	int		step_y;
	bool	axis;

	step_x = calculate_step_x_direction(ray, vars);
	step_y = calculate_step_y_direction(ray, vars);
	while(1)
	{
		// x方向またはy方向のいずれかで次のマップのブロックにジャンプする。
		if(ray->x_side_distance < ray->y_side_distance)
		{
			ray->x_side_distance += ray->x_delta_distance;
			ray->current_x_in_map += step_x;
			axis = X_AXIS;
		}
		else
		{
			ray->y_side_distance += ray->y_delta_distance;
			ray->current_y_in_map += step_y;
			axis = Y_AXIS;
		}
		if (is_hit_wall(ray, info))
			break ;
	}
	return (axis);
}