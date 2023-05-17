/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:32:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/17 14:24:30 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_one_block(t_data *data, int draw_y, int draw_x, int color)
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
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	start_i;
	int	end_i;
	int	start_j;
	int	end_j;
	int	i;
	int	j;

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
	while (i < end_i)
	{
		// printf("i = %d\n", i);
		// printf("j = %d\n", j);
		j = start_j;
		// printf("\x1b[32m %d,%d\x1b[0m",i,j);
		while (j < end_j)
		{
			if (i < 0)
			{
				draw_one_block(data, i - start_i, j - start_j, PINK);
			}
			else if (i >= info->map->height)
			{
				// printf("\x1b[31 map->height の条件式に入った\x1b[0m\n");
				draw_one_block(data, i - start_i, j - start_j, YELLOW);
			}
			else if (info->map->map_data[i][j] == '1')
			{
				draw_one_block(data, i - start_i, j - start_j, GREEN);
			}
			else if (info->map->map_data[i][j] == '0')
			{
				draw_one_block(data, i - start_i, j - start_j, WHITE);
			}
			else if (info->map->map_data[i][j] == 'N'
					|| info->map->map_data[i][j] == 'S'
					|| info->map->map_data[i][j] == 'E'
					|| info->map->map_data[i][j] == 'W')
				draw_one_block(data, i - start_i, j - start_j, BLUE);
			else
				draw_one_block(data, i - start_i, j - start_j, RED);
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
