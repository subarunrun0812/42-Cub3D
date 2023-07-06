/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:20:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 19:41:07 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_ray_player_direction(t_info *info, int start_x, int start_y)
{
	int	ray_len;
	int	middle_ray_x;
	int	middle_ray_y;

	ray_len = BLOCK_SIZE / 2;
	middle_ray_x = 0;
	middle_ray_y = 0;
	while (ray_len < 100)
	{
		middle_ray_x = (ray_len * info->vars->y_dir);
		middle_ray_y = (ray_len * info->vars->x_dir);
		my_mlx_pixel_put(info->data, start_x + (info->map->x_player * BLOCK_SIZE
				+ (BLOCK_SIZE / 2)) + middle_ray_x, start_y
			+ (info->map->y_player * BLOCK_SIZE + (BLOCK_SIZE / 2))
			+ middle_ray_y, BLACK);
		ray_len++;
	}
}

static int	get_central_draw_color(t_info *info, int x, int y)
{
	if (info->map->map_data[y][x] == ' ')
	{
		return (NO_COLOR);
	}
	else if (info->map->map_data[y][x] == '1')
	{
		return (MAP_GREEN);
	}
	else if (info->map->map_data[y][x] == '0')
	{
		return (MAP_WHITE);
	}
	else if (info->map->map_data[y][x] == 'N'
		|| info->map->map_data[y][x] == 'S' || info->map->map_data[y][x] == 'E'
		|| info->map->map_data[y][x] == 'W')
	{
		info->map->x_player = x;
		info->map->y_player = y;
		return (BLUE);
	}
	else
		return (MAP_RED);
}

static void	draw_central_map(t_info *info)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	color;

	start_x = (WIN_WIDTH / 2) - ((maxwidth_length(info->map) * BLOCK_SIZE) / 2);
	start_y = (WIN_HEIGHT / 2) - (((info->map->height) * BLOCK_SIZE) / 2);
	y = 0;
	while (y < info->map->height)
	{
		x = 0;
		while (x < mapdata_width_length(info->map->map_data[y]) + 1)
		{
			color = get_central_draw_color(info, x, y);
			if (color != NO_COLOR)
			{
				central_draw_one_block(info, start_x + (x * BLOCK_SIZE), start_y
					+ (y * BLOCK_SIZE), color);
			}
			x++;
		}
		y++;
	}
}

void	central_map(t_info *info)
{
	int	start_x;
	int	start_y;

	draw_central_map(info);
	start_x = (WIN_WIDTH / 2) - ((maxwidth_length(info->map) * BLOCK_SIZE) / 2);
	start_y = (WIN_HEIGHT / 2) - (((info->map->height) * BLOCK_SIZE) / 2);
	draw_ray_player_direction(info, start_x, start_y);
	draw_ray_player_fov(info, start_x, start_y);
	return ;
}
