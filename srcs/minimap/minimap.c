/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:32:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/17 15:25:49 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_one_block(t_data *data, int draw_x, int draw_y, int color)
{
	int	x;
	int	y;

	x = (draw_x * BLOCK_SIZE);
	while (x < ((draw_x * BLOCK_SIZE) + BLOCK_SIZE))
	{
		y = (draw_y * BLOCK_SIZE);
		while (y < ((draw_y * BLOCK_SIZE) + BLOCK_SIZE))
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	range_to_display_with_player(t_info *info, t_data *data)
{
	// printf("range_to_display_with_player\n");
	int		start_i;
	int		end_i;
	int		start_j;
	int		end_j;
	int		i;
	int		j;

	// printf("\x1b[32mplayer = (%f,%f)\x1b[0m\n",info->pos->y,info->pos->x);
	// マップのx,y軸の表示する範囲
	start_i = (int)info->vars->x_position_vector - DISPLAY_RADIUS / BLOCK_SIZE;
	end_i = (int)info->vars->x_position_vector + DISPLAY_RADIUS / BLOCK_SIZE;
	if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
    	end_i++;

	start_j = (int)info->vars->y_position_vector - DISPLAY_RADIUS / BLOCK_SIZE;
	end_j = (int)info->vars->y_position_vector + DISPLAY_RADIUS / BLOCK_SIZE;
	if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
    	end_j++;
	i = start_i;
	j = start_j;
	while (i < end_i)
	{
		j = start_j;
		while (j < end_j)
		{
			//マップがいの場合
			if (i < 0 || i >= info->map->height ||
				j < 0 || j > mapdata_width_length(info->map->map_data[i])
				 || info->map->map_data[i][j] == ' ')
			{
				draw_one_block(data, j - start_j, i - start_i, MAP_PINK);
			}
			else if (info->map->map_data[i][j] == '1'
			|| info->map->map_data[i][j] == '2' || info->map->map_data[i][j] == '3'
			|| info->map->map_data[i][j] == '4')
			{
				draw_one_block(data, j - start_j, i - start_i, MAP_GREEN);
			}
			else if (info->map->map_data[i][j] == '0')
			{
				draw_one_block(data, j - start_j, i - start_i, MAP_WHITE);
			}
			else if (info->map->map_data[i][j] == 'N'
					|| info->map->map_data[i][j] == 'S'
					|| info->map->map_data[i][j] == 'E'
					|| info->map->map_data[i][j] == 'W')
				draw_one_block(data, j - start_j, i - start_i, BLUE);
			else
				draw_one_block(data, j - start_j, i - start_i, MAP_RED);
			j++;
		}
		i++;
	}
}

// printf("info->pos->x = %d\n", (int)info->pos->x);
// printf("info->pos->y = %d\n", (int)info->pos->y);
// printf("start_x = %d\n", start_x);
// printf("start_y = %d\n", start_y);
// printf("end_x = %d\n", end_x);
// printf("end_y = %d\n", end_y);
// printf("start_i = %d\n", start_i);
// printf("end_i = %d\n", end_i);
// printf("start_j = %d\n", start_j);
// printf("end_j = %d\n", end_j);
// printf("i = %d\n", i);
// printf("j = %d\n", j);
int	minimap(t_info *info, t_data *data)
{
	// debug_print_mapdata(info);
	// printf("map->height = %d\n",info->map->height);
	//minimapの画像表示
	// data->img = mlx_new_image(info->vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	range_to_display_with_player(info, data);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, data->img, 0, 0);
	return (0);
}
