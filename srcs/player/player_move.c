/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:58:58 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/15 13:25:41 by susasaki         ###   ########.fr       */
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
    t_pos dst;
    // printf("~~ player_move ~~\n");
    dst.x = 0;
    dst.y = 0;
    if (keycode == W_KEY)
    {
        dst.y -= MOVE_DISTANCE;
        printf("W");
    }
    else if (keycode == S_KEY)
    {
        dst.y += MOVE_DISTANCE;
        printf("S");
    }
    else if (keycode == D_KEY)
    {
        dst.x += MOVE_DISTANCE;
        printf("D");
    }
    else if (keycode == A_KEY)
    {
        dst.x -= MOVE_DISTANCE;
        printf("A");
    }
    info->pos->y += dst.y;
    info->pos->x += dst.x;
    printf("\x1b[32mplayer = %c (%f,%f)\x1b[0m\n",info->map->map_data[(int)info->pos->y][(int)info->pos->x]
    ,info->pos->y,info->pos->x);
    if (info->map->map_data[(int)(info->pos->y)][(int)(info->pos->x)] == '0')
    {
        info->map->map_data[(int)(info->pos->y - dst.y)][(int)(info->pos->x - dst.x)] = '0';
        info->map->map_data[(int)(info->pos->y)][(int)(info->pos->x)] = 'N';
        // debug_print_mapdata(info);
    }
    else if (info->map->map_data[(int)(info->pos->y)][(int)(info->pos->x)] == '1')
    {
        info->pos->y -= dst.y;
        info->pos->x -= dst.x;
    }
    range_to_display_with_player(info,info->data);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, info->data->img, 0, 0);
    // printf("\x1b[32m:player = (%f,%f)\x1b[0m\n",info->pos->y,info->pos->x);
}