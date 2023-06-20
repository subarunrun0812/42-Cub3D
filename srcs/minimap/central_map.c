/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:20:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/20 16:45:31 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	central_draw_one_block(t_data *data, int draw_x, int draw_y, int color)
{
	int	x;
	int	y;

	x = draw_x;
	while (x < draw_x + BLOCK_SIZE)
	{
		y = draw_y;
		while (y < (draw_y + BLOCK_SIZE))
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}


void central_map(t_info *info)
{
    /*
    map中央を求める
    mapの縦横の大きさか描画スタート地点を決める
    列ごとに描画する
    */
    int x;
    int y;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    
    //描画開始地点を求める
    start_x = (WIN_WIDTH / 2) - ((mapdata_maxwidth_length(info->map) * BLOCK_SIZE) / 2);
    start_y = (WIN_HEIGHT / 2) - (((info->map->height) * BLOCK_SIZE) / 2);
    end_y = info->map->height;
    y = 0;
    
    // printf("start_x = %d\n",start_x);
    // printf("start_y = %d\n",start_y);
    // printf("end_y = %d\n",end_y);
    while (y < end_y)
    {
        x = 0;
        end_x = mapdata_width_length(info->map->map_data[y]);
        // printf("x = %d\n",x);
        // printf("end_x = %d\n",end_x);
        while (x < end_x + 1)
        {
            // printf("xy = [%d][%d]\n",x,y);
			if (info->map->map_data[y][x] == ' ')
			{
				;
			}
			else if (info->map->map_data[y][x] == '1'
			|| info->map->map_data[y][x] == '2' || info->map->map_data[y][x] == '3'
			|| info->map->map_data[y][x] == '4')
			{
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE), start_y + (y * BLOCK_SIZE), MAP_GREEN);
			}
			else if (info->map->map_data[y][x] == '0')
			{
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE), start_y + (y * BLOCK_SIZE), MAP_WHITE);
			}
			else if (info->map->map_data[y][x] == 'N'
					|| info->map->map_data[y][x] == 'S'
					|| info->map->map_data[y][x] == 'E'
					|| info->map->map_data[y][x] == 'W')
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE), start_y + (y * BLOCK_SIZE), BLUE);
			else
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE), start_y + (y * BLOCK_SIZE), MAP_RED);
			x++;
		}
		y++;
    }
    return ;
}