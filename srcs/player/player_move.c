/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:58:58 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/16 16:19:21 by susasaki         ###   ########.fr       */
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
    // t_player dst;
    // // printf("~~ player_move ~~\n");
    // dst.pos_x = 0;
    // dst.pos_y = 0;
    // if (keycode == W_KEY)
    // {
    //     dst.pos_y -= MOVE_DISTANCE;
    //     printf("W");
    // }
    // else if (keycode == S_KEY)
    // {
    //     dst.pos_y += MOVE_DISTANCE;
    //     printf("S");
    // }
    // else if (keycode == D_KEY)
    // {
    //     dst.pos_x += MOVE_DISTANCE;
    //     printf("D");
    // }
    // else if (keycode == A_KEY)
    // {
    //     dst.pos_x -= MOVE_DISTANCE;
    //     printf("A");
    // }
    // info->player->pos_y += dst.pos_y;
    // info->player->pos_x += dst.pos_x;
    // printf("\x1b[32mplayer = %c (%f,%f)\x1b[0m\n",info->map->map_data[(int)info->player->pos_y][(int)info->player->pos_x]
    // ,info->player->pos_y,info->player->pos_x);
    // if (info->map->map_data[(int)(info->player->pos_y)][(int)(info->player->pos_x)] == '0')
    // {
    //     info->map->map_data[(int)(info->player->pos_y - dst.pos_y)][(int)(info->player->pos_x - dst.pos_x)] = '0';
    //     info->map->map_data[(int)(info->player->pos_y)][(int)(info->player->pos_x)] = 'N';
    //     // debug_print_mapdata(info);
    // }
    // else if (info->map->map_data[(int)(info->player->pos_y)][(int)(info->player->pos_x)] == '1')
    // {
    //     info->player->pos_y -= dst.pos_y;
    //     info->player->pos_x -= dst.pos_x;
    // }
    (void)keycode;
    range_to_display_with_player(info,info->data);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, info->data->img, 0, 0);
    // printf("\x1b[32m:player = (%f,%f)\x1b[0m\n",info->pos->y,info->pos->x);
}