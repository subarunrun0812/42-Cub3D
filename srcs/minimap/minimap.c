/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:32:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/13 21:38:33 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void draw_one_block(t_data *data,int i, int j, int color)
{
    int x = (i * BLOCK_SIZE);
    while (x < ((i * BLOCK_SIZE) + BLOCK_SIZE - 1))
    {
        int y = (j * BLOCK_SIZE);
        while (y < ((j * BLOCK_SIZE) + BLOCK_SIZE))
        {
            //
            my_mlx_pixel_put(data, y, x, color);
            y++;
        }
        x++;
    }
}

void range_to_display_with_player(t_info *info, t_data *data)
{
    // マップのx,y軸の表示する範囲
    int diameter;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int x;
    int y;

    diameter = 200;

    start_x = info->pos->x - (diameter / 2);
    start_y = info->pos->y - (diameter / 2);
    end_x = info->pos->x + (diameter / 2);
    end_y = info->pos->y + (diameter / 2);
    x = start_x;
    y = start_y;
    
    int i = 0;
    int j = 0;
    while (info->map->map_data[i])
    {
        j = 0;
        while (info->map->map_data[i][j])
        {
            if (info->map->map_data[i][j] == '1')
            {
                draw_one_block(data,i,j,WHITE);
            }
            else if (info->map->map_data[i][j] == '0')
            {
                draw_one_block(data,i,j,WHEAT);
            }
            else
                draw_one_block(data,i,j,WHEAT);
            j++;
        }
        i++;
    }
}

int minimap(t_info *info)
{
    // printf("map->height = %d\n",info->map->height);
    t_data data;
    //minimapの画像表示
    data.img = mlx_new_image(info->vars->mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
                                &data.endian);
    //TODO:playerからのx,y軸において半径100pixelを描画する
    range_to_display_with_player(info,&data);
    mlx_put_image_to_window(info->vars->mlx, info->vars->win, data.img, 0, 0);

    return (0);
}
