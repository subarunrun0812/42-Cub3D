/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:04:19 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 19:04:44 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	corner_map(t_info *info, t_data *data)
{
	int	start_i;
	int	end_i;
	int	start_j;
	int	end_j;
	int	i;
	int	j;
	int	ray_len;
	int	tmp_x;
	int	tmp_y;

	(void)data;
	// マップのx,y軸の表示する範囲
	start_i = (int)info->vars->x_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	end_i = (int)info->vars->x_pos + DISPLAY_RADIUS / BLOCK_SIZE;
	if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
		end_i++;
	start_j = (int)info->vars->y_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	end_j = (int)info->vars->y_pos + DISPLAY_RADIUS / BLOCK_SIZE;
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
			if (i < 0 || i >= info->map->height || j < 0
				|| j > mapdata_width_length(info->map->map_data[i])
				|| info->map->map_data[i][j] == ' ')
			{
				draw_one_block(info, j - start_j, i - start_i, MAP_PINK);
			}
			else if (info->map->map_data[i][j] == '1'
				|| info->map->map_data[i][j] == '2'
				|| info->map->map_data[i][j] == '3'
				|| info->map->map_data[i][j] == '4')
			{
				draw_one_block(info, j - start_j, i - start_i, MAP_GREEN);
			}
			else if (info->map->map_data[i][j] == '0')
			{
				draw_one_block(info, j - start_j, i - start_i, MAP_WHITE);
			}
			else if (info->map->map_data[i][j] == 'N'
				|| info->map->map_data[i][j] == 'S'
				|| info->map->map_data[i][j] == 'E'
				|| info->map->map_data[i][j] == 'W')
			{
				draw_one_block(info, j - start_j, i - start_i, BLUE);
				info->map->x_player = j;
				info->map->y_player = i;
			}
			else
				draw_one_block(info, j - start_j, i - start_i, MAP_RED);
			j++;
		}
		i++;
	}
	ray_len = BLOCK_SIZE / 2;
	tmp_x = 0;
	tmp_y = 0;
	while (ray_len < 30)
	{
		tmp_x = (ray_len * info->vars->y_dir);
		tmp_y = (ray_len * info->vars->x_dir);
		my_mlx_pixel_put(info->data, DISPLAY_RADIUS + (BLOCK_SIZE / 2) + tmp_x,
			DISPLAY_RADIUS + (BLOCK_SIZE / 2) + tmp_y, FUCHSIA);
		ray_len++;
	}
}
