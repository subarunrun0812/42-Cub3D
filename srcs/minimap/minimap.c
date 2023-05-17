/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:32:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/17 15:38:56 by susasaki         ###   ########.fr       */
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
			//
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	range_to_display_with_player(t_info *info, t_data *data)
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		start_i;
	int		end_i;
	int		start_j;
	int		end_j;
	int		i;
	int		j;

	// printf("\x1b[32mplayer = (%f,%f)\x1b[0m\n",info->pos->y,info->pos->x);
	// マップのx,y軸の表示する範囲
	start_x = ((int)info->pos->x * BLOCK_SIZE + (BLOCK_SIZE / 2))
		- DISPLAY_RADIUS;
	start_y = ((int)info->pos->y * BLOCK_SIZE + (BLOCK_SIZE / 2))
		- DISPLAY_RADIUS;
	end_x = ((int)info->pos->x * BLOCK_SIZE + (BLOCK_SIZE / 2))
		+ DISPLAY_RADIUS;
	end_y = ((int)info->pos->y * BLOCK_SIZE + (BLOCK_SIZE / 2))
		+ DISPLAY_RADIUS;
	start_i = start_y / BLOCK_SIZE;
	end_i = end_y / BLOCK_SIZE;
	if (end_y % BLOCK_SIZE != 0)
	{
		printf("end_i = %d\n", end_i);
		end_i++;
	}
	start_j = start_x / BLOCK_SIZE;
	end_j = end_x / BLOCK_SIZE;
	if (end_x % BLOCK_SIZE != 0)
	{
		printf("end_j = %d\n", end_j);
		end_j++;
	}
	i = start_i;
	j = start_j;
	// int map_radius = DISPLAY_RADIUS / BLOCK_SIZE;
	// int map_top = (int)info->pos->y - map_radius;
	debug_print_mapdata(info);
	while (i < end_i)
	{
		// printf("i = %d\n", i);
		// printf("j = %d\n", j);
		j = start_j;
		// printf("\x1b[32m %d,%d\x1b[0m",i,j);
		while (j < end_j)
		{
			//map_top + i - start_i > map_radius * 2
			if (i < 0 || i >= info->map->height ||
				j < 0 || j > mapdata_width_length(info->map->map_data[i]))
			{
				draw_one_block(data, j - start_j, i - start_i, PINK);
			}
			else if (info->map->map_data[i][j] == '1')
			{
				draw_one_block(data, j - start_j, i - start_i, GREEN);
			}
			else if (info->map->map_data[i][j] == '0')
			{
				draw_one_block(data, j - start_j, i - start_i, WHITE);
			}
			else if (info->map->map_data[i][j] == 'N'
					|| info->map->map_data[i][j] == 'S'
					|| info->map->map_data[i][j] == 'E'
					|| info->map->map_data[i][j] == 'W')
				draw_one_block(data, j - start_j, i - start_i, BLUE);
			else
				draw_one_block(data, j - start_j, i - start_i, RED);
			j++;
		}
		i++;
	}
	// #define MINIMAP_WIDTH 10
	// #define MINIMAP_HEIGHT 20
	// #define PLAYER_POS_Y (MINIMAP_WIDTH / 2)
	// #define PLAYER_POS_X (MINIMAP_HEIGHT / 2)
	/*akibaコード
	
	y = 0;
	x = 0;
	map_radius = DISPLAY_RADIUS / BLOCK_SIZE;
	map_top = (int)info->pos->y - map_radius;
	map_left = (int)info->pos->x - map_radius;
	while (y < map_radius * 2)
	{
		x = 0;
		while (x < map_radius * 2)
		{
			if (map_top + y < 0 || map_left + x < 0 || 
				map_left + x > map_radius * 2 || map_top + y > map_radius * 2)
				draw_one_block(data, y, x, PINK);
			else
			{
				identifer = info->map->map_data[map_top + y][map_left + x];
				if (identifer == '1')
					draw_one_block(data, y, x, GREEN);
				else if (identifer == '0')
					draw_one_block(data, y, x, WHITE);
				else if (identifer == 'N')
					draw_one_block(data, y, x, BLUE);
				else
					draw_one_block(data, y, x, RED);
			}
			x++;
		}
		y++;
	}
	debug_print_mapdata(info);
	*/
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
	debug_print_mapdata(info);
	// printf("map->height = %d\n",info->map->height);
	//minimapの画像表示
	data->img = mlx_new_image(info->vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	//TODO:playerからのx,y軸において半径100pixelを描画する
	range_to_display_with_player(info, data);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, data->img, 0, 0);
	return (0);
}
