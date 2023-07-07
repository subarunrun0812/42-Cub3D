/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:16:26 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 15:21:05 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
void	corner_map(t_info *info, t_data *data)
{
	int	start_y;
	int	end_y;
	int	start_x;
	int	end_x;
	int	_y;
	int	_x;
	int	ray_len;
	int	tmp_x;
	int	tmp_y;

	(void)data;
	// マップのx,y軸の表示する範囲
	start_y = (int)info->vars->x_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	end_y = (int)info->vars->x_pos + DISPLAY_RADIUS / BLOCK_SIZE;
	if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
		end_y++;
	start_x = (int)info->vars->y_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	end_x = (int)info->vars->y_pos + DISPLAY_RADIUS / BLOCK_SIZE;
	if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
		end_x++;
	_y = start_y;
	_x = start_x;
	while (_y < end_y)
	{
		_x = start_x;
		while (_x < end_x)
		{
			//マップがいの場合
			if (_y < 0 || _y >= info->map->height || _x < 0
				|| _x > mapdata_width_length(info->map->map_data[_y])
				|| info->map->map_data[_y][_x] == ' ')
			{
				corner_draw_one_block(info, _x - start_x, _y - start_y, MAP_PINK);
			}
			else if (info->map->map_data[_y][_x] == '1'
				|| info->map->map_data[_y][_x] == '2'
				|| info->map->map_data[_y][_x] == '3'
				|| info->map->map_data[_y][_x] == '4')
			{
				corner_draw_one_block(info, _x - start_x, _y - start_y, MAP_GREEN);
			}
			else if (info->map->map_data[_y][_x] == '0')
			{
				corner_draw_one_block(info, _x - start_x, _y - start_y, MAP_WHITE);
			}
			else if (info->map->map_data[_y][_x] == 'N'
				|| info->map->map_data[_y][_x] == 'S'
				|| info->map->map_data[_y][_x] == 'E'
				|| info->map->map_data[_y][_x] == 'W')
			{
				corner_draw_one_block(info, _x - start_x, _y - start_y, BLUE);
				info->map->x_player = _x;
				info->map->y_player = _y;
			}
			else
				corner_draw_one_block(info, _x - start_x, _y - start_y, MAP_RED);
			_x++;
		}
		_y++;
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
