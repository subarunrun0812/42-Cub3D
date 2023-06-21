/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:44:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/19 22:21:28 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

void init_player_coordinate(t_player *player,t_map *map)
{
    int i;
    int j;
    i = 0;
    while (map->map_data[i])
    {
        j = 0;
        while (map->map_data[i][j])
        {
            if (map->map_data[i][j] == 'N' || map->map_data[i][j] == 'S'
            || map->map_data[i][j] == 'W' || map->map_data[i][j] == 'E')
            {
                player->pos_x = i;
                player->pos_y = j;
                // printf("map->map_data[%d][%d] == %c\n",i,j,map->map_data[i][j]);
                return ;
            }
            j++;
        }
        i++;
    }
    return ;
}

int player_coordinate(t_info *info)
{
    init_player_coordinate(info->player,info->map);
    return (0);
}