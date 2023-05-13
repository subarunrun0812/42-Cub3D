/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:44:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/11 18:01:01 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

static void init_player_coordinate(t_pos *pos,t_map *map)
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
                pos->x = i;
                pos->y = j;
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
    init_player_coordinate(info->pos,info->map);
    return (0);
}