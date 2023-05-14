/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:58:58 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/14 22:49:20 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int width_len(t_map *map,int i)
{
    int j;
    j = 0;
    while (map->map_data[i][j] != '\0')
    {
        j++;
    }
    return (j);
}

// void    player_move_in_minimap(t_info *info)
// {
    
// }

void    player_move(t_info *info, int keycode)
{
    // printf("~~ player_move ~~\n");
    if (keycode == W_KEY)
    {
        info->pos->y += 0.2;
    }
    else if (keycode == S_KEY)
    {
        info->pos->y -= 0.2;
    }
    range_to_display_with_player(info,info->data);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, info->data->img, 0, 0);
    printf("\x1b[32mplayer = (%f,%f)\x1b[0m\n",info->pos->x,info->pos->y);
}