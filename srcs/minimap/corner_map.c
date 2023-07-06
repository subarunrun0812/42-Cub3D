/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:16:26 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 19:25:18 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_draw_color(t_info *info, int i, int j)
{
	char	pos;

	pos = info->map->map_data[i][j];
	if (i < 0 || i >= info->map->height || j < 0
		|| j > mapdata_width_length(info->map->map_data[i]) || pos == ' ')
		return (MAP_PINK);
	else if (pos == '1' || pos == '2' || pos == '3' || pos == '4')
		return (MAP_GREEN);
	else if (pos == '0')
		return (MAP_WHITE);
	else if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
	{
		info->map->x_player = j;
		info->map->y_player = i;
		return (BLUE);
	}
	else
		return (MAP_RED);
}

void	draw_corner_map(t_info *info, int end_i, int end_j)
{
	int	i;
	int	j;
	int	start_i;
	int	start_j;
	int	color;

	start_i = (int)info->vars->x_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	start_j = (int)info->vars->y_pos - DISPLAY_RADIUS / BLOCK_SIZE;
	i = start_i;
	j = start_j;
	while (i < end_i)
	{
		j = start_j;
		while (j < end_j)
		{
			color = get_draw_color(info, i, j);
			draw_one_block(info, j - start_j, i - start_i, color);
			j++;
		}
		i++;
	}
}

void	draw_ray(t_info *info, int ray_len)
{
	int	tmp_x;
	int	tmp_y;

	while (ray_len < 30)
	{
		tmp_x = (ray_len * info->vars->y_dir);
		tmp_y = (ray_len * info->vars->x_dir);
		my_mlx_pixel_put(info->data, DISPLAY_RADIUS + (BLOCK_SIZE / 2) + tmp_x,
			DISPLAY_RADIUS + (BLOCK_SIZE / 2) + tmp_y, FUCHSIA);
		ray_len++;
	}
}

void	corner_map(t_info *info, t_data *data)
{
	int	end_i;
	int	end_j;
	int	ray_len;

	(void)data;
	end_i = (int)info->vars->x_pos + DISPLAY_RADIUS / BLOCK_SIZE;
	if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
		end_i++;
	end_j = (int)info->vars->y_pos + DISPLAY_RADIUS / BLOCK_SIZE;
	if (DISPLAY_RADIUS % BLOCK_SIZE != 0)
		end_j++;
	draw_corner_map(info, end_i, end_j);
	ray_len = BLOCK_SIZE / 2;
	draw_ray(info, ray_len);
}
