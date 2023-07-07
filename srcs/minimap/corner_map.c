/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:16:26 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 15:38:25 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	determine_block_color(t_info *info, int _x, int _y)
{
	if (_y < 0 || _y >= info->map.height || _x < 0
		|| _x > mapdata_width_length(info->map.map_data[_y])
		|| info->map.map_data[_y][_x] == ' ')
		return (MAP_PINK);
	else if (info->map.map_data[_y][_x] == '1'
		|| info->map.map_data[_y][_x] == '2'
		|| info->map.map_data[_y][_x] == '3'
		|| info->map.map_data[_y][_x] == '4')
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

void draw_block(t_info *info, int _x, int _y, int start_x, int start_y)
{
    int color = determine_block_color(info, _x, _y);
    corner_draw_one_block(info, _x - start_x, _y - start_y, color);
}


void draw_map(t_info *info, int start_x, int start_y, int end_x, int end_y)
{
    int _x, _y;

    _y = start_y;
    while (_y < end_y)
    {
        _x = start_x;
        while (_x < end_x)
        {
            draw_block(info, _x, _y, start_x, start_y);
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
    int	start_y;
    int	end_y;
    int	start_x;
    int	end_x;

    (void)data;
    // マップのx,y軸の表示する範囲
    start_y = (int)info->vars.x_pos - DISPLAY_RADIUS / BLOCK_SIZE;
    end_y = (int)info->vars.x_pos + DISPLAY_RADIUS / BLOCK_SIZE;
    if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
        end_y++;
    start_x = (int)info->vars.y_pos - DISPLAY_RADIUS / BLOCK_SIZE;
    end_x = (int)info->vars.y_pos + DISPLAY_RADIUS / BLOCK_SIZE;
    if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
        end_x++;

    draw_map(info, start_x, start_y, end_x, end_y);
    draw_ray(info);
}
