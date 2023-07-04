/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updata_pos_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:20 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/02 16:01:20 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	updata_pos_map(t_vars *vars, t_info *info, int keycode)
{
	// map情報を更新
	if (info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] == '0')
	{
		if (keycode == W_KEY)
		{
			info->map->map_data[(int)(vars->x_position_vector
				- (vars->x_direction
					* MOVE_DISTANCE))][(int)(vars->y_position_vector
				- (vars->y_direction * MOVE_DISTANCE))] = '0';
			info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] = 'N';
		}
		else if (keycode == S_KEY)
		{
			info->map->map_data[(int)(vars->x_position_vector
				+ (vars->x_direction
					* MOVE_DISTANCE))][(int)(vars->y_position_vector
				+ (vars->y_direction * MOVE_DISTANCE))] = '0';
			info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] = 'N';
		}
	}
	else if (info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] == '1')
	{
		vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
		vars->y_position_vector -= vars->y_direction * MOVE_DISTANCE;
	}
}