/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:16:26 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/11 18:30:14 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	determine_block_color(t_info *info, int _x, int _y)
{
	if (_y < 0 || _y >= info->map.height || _x < 0
		|| _x > mapdata_width_length(info->map.map_data[_y])
		|| info->map.map_data[_y][_x] == ' ')
		return (MAP_PINK);
	else if (info->map.map_data[_y][_x] == '1')
		return (MAP_GREEN);
	else if (info->map.map_data[_y][_x] == '0')
		return (MAP_WHITE);
	else if (info->map.map_data[_y][_x] == 'N'
		|| info->map.map_data[_y][_x] == 'S'
		|| info->map.map_data[_y][_x] == 'E'
		|| info->map.map_data[_y][_x] == 'W')
	{
		info->map.x_player = _x;
		info->map.y_player = _y;
		return (BLUE);
	}
	else
		return (MAP_RED);
}

void	draw_map(t_info *info, int end_x, int end_y)
{
	int	_x;
	int	_y;
	int	start_y;
	int	start_x;

	start_y = (int)info->vars.x_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	start_x = (int)info->vars.y_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	_y = start_y;
	while (_y < end_y)
	{
		_x = start_x;
		while (_x < end_x)
		{
			corner_draw_one_block(info, _x - start_x, _y - start_y,
				determine_block_color(info, _x, _y));
			_x++;
		}
		_y++;
	}
}

void	draw_ray(t_info *info)
{
	int	ray_len;
	int	tmp_x;
	int	tmp_y;

	ray_len = BLOCK_SIZE / 2;
	tmp_x = 0;
	tmp_y = 0;
	while (ray_len < 30)
	{
		tmp_x = (ray_len * info->vars.y_dir);
		tmp_y = (ray_len * info->vars.x_dir);
		my_mlx_pixel_put(&info->data, DISPLAY_RADIUS + (BLOCK_SIZE / 2) + tmp_x,
			DISPLAY_RADIUS + (BLOCK_SIZE / 2) + tmp_y, FUCHSIA);
		ray_len++;
	}
}

void	corner_map(t_info *info, t_data *data)
{
	int	end_y;
	int	end_x;

	(void)data;
	end_y = (int)info->vars.x_pos + DISPLAY_RADIUS / BLOCK_SIZE;
	end_x = (int)info->vars.y_pos + DISPLAY_RADIUS / BLOCK_SIZE;
	draw_map(info, end_x, end_y);
	draw_ray(info);
}
