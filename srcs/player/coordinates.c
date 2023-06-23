/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:44:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/23 14:03:14 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

void init_player_coordinate(t_player *player,t_map *map)
{
    int _y;
    int _x;
    _y = 0;
    while (map->map_data[_y])
    {
        _x = 0;
        while (map->map_data[_y][_x])
        {
            if (map->map_data[_y][_x] == 'N' || map->map_data[_y][_x] == 'S'
            || map->map_data[_y][_x] == 'W' || map->map_data[_y][_x] == 'E')
            {
                // printf("init _y = %d,pos_x =%d\n",_y,_x);
                player->pos_y = _y;
                player->pos_x = _x;
                // printf("map->map_data[%d][%d] == %c\n",i,j,map->map_data[i][j]);
                return ;
            }
            _x++;
        }
        _y++;
    }
    return ;
}

int player_coordinate(t_info *info)
{
    init_player_coordinate(info->player,info->map);
    return (0);
}