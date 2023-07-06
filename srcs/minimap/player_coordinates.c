/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:44:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 19:41:41 by susasaki         ###   ########.fr       */
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

void	init_player_coordinate(t_map *map, t_info *info)
{
	int	_y;
	int	_x;

	_y = 0;
	while (map->map_data[_y])
	{
		_x = 0;
		while (map->map_data[_y][_x])
		{
			if (map->map_data[_y][_x] == 'N' || map->map_data[_y][_x] == 'S'
				|| map->map_data[_y][_x] == 'W' || map->map_data[_y][_x] == 'E')
			{
				info->map->y_player = _y;
				info->map->x_player = _x;
				return ;
			}
			_x++;
		}
		_y++;
	}
	return ;
}
