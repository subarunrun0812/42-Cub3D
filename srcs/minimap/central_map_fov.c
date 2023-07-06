/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_map_fov.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:36:53 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 19:41:04 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_single_fov(t_info *info, int start_x, int start_y,
		int direction_multiplier)
{
	int	ray_len;
	int	middle_ray_x;
	int	middle_ray_y;

	ray_len = 0;
	while (ray_len < 100)
	{
		middle_ray_x = (ray_len * (info->vars->y_dir + (info->vars->y_cam_plane
					* direction_multiplier)));
		middle_ray_y = (ray_len * (info->vars->x_dir + (info->vars->x_cam_plane
					* direction_multiplier)));
		my_mlx_pixel_put(info->data, start_x + (info->map->x_player * BLOCK_SIZE
				+ (BLOCK_SIZE / 2)) + middle_ray_x, start_y
			+ (info->map->y_player * BLOCK_SIZE + (BLOCK_SIZE / 2))
			+ middle_ray_y, RED);
		ray_len++;
	}
}

void	draw_ray_player_fov(t_info *info, int start_x, int start_y)
{
	draw_single_fov(info, start_x, start_y, -1);
	draw_single_fov(info, start_x, start_y, 1);
}
