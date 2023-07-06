/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:44:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 16:46:51 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
