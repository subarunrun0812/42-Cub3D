/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:44:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/18 14:42:17 by susasaki         ###   ########.fr       */
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
                player->pos_y = i;
                player->pos_x = j;
                printf("map->map_data[%d][%d] == %c\n",i,j,map->map_data[i][j]);
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