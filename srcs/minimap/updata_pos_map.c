/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updata_pos_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:03:20 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 16:46:44 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	updata_pos_map(t_vars *vars, t_info *info, int keycode)
{
	if (info->map->map_data[(int)(vars->x_pos)][(int)(vars->y_pos)] == '0')
	{
		if (keycode == W_KEY)
		{
			info->map->map_data
			[(int)(vars->x_pos - (vars->x_dir * MOVE_DIST))]
			[(int)(vars->y_pos - (vars->y_dir * MOVE_DIST))] = '0';
			info->map->map_data[(int)(vars->x_pos)][(int)(vars->y_pos)] = 'N';
		}
		else if (keycode == S_KEY)
		{
			info->map->map_data
			[(int)(vars->x_pos + (vars->x_dir * MOVE_DIST))]
			[(int)(vars->y_pos + (vars->y_dir * MOVE_DIST))] = '0';
			info->map->map_data[(int)(vars->x_pos)][(int)(vars->y_pos)] = 'N';
		}
	}
	else if (info->map->map_data[(int)(vars->x_pos)][(int)(vars->y_pos)] == '1')
	{
		vars->x_pos -= vars->x_dir * MOVE_DIST;
		vars->y_pos -= vars->y_dir * MOVE_DIST;
	}
}
