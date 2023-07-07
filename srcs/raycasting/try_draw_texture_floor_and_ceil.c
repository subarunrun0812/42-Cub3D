/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_draw_texture_floor_and_ceil.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 14:13:29 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_draw_background(t_draw_background *draw, t_vars *vars,
		int y_coord, float vert_pos_cam)
{
	float	ray_dir_left[2];
	float	ray_dir_right[2];
	float	row_dist;

	ray_dir_left[X_AXIS] = vars->x_dir - vars->x_cam_plane;
	ray_dir_left[Y_AXIS] = vars->y_dir - vars->y_cam_plane;
	ray_dir_right[X_AXIS] = vars->x_dir + vars->x_cam_plane;
	ray_dir_right[Y_AXIS] = vars->y_dir + vars->y_cam_plane;
	row_dist = vert_pos_cam / y_coord;
	draw->x_span = row_dist * (ray_dir_right[X_AXIS]
			- ray_dir_left[X_AXIS]) / WIN_WIDTH;
	draw->y_span = row_dist * (ray_dir_right[Y_AXIS]
			- ray_dir_left[Y_AXIS]) / WIN_WIDTH;
	draw->x_coord = vars->x_pos + row_dist
		* ray_dir_left[X_AXIS];
	draw->y_coord = vars->y_pos + row_dist
		* ray_dir_left[Y_AXIS];
}

static int	draw_texture_floor(t_info *info)
{
	int					coord_screen[2];
	int					cell[2];
	t_draw_background	draw;

	coord_screen[Y_AXIS] = (WIN_HEIGHT / 2) - 1;
	while (coord_screen[Y_AXIS] < WIN_HEIGHT)
	{
		set_draw_background(&draw, &info->vars,
			coord_screen[Y_AXIS] - (WIN_HEIGHT / 2), 0.5 * WIN_HEIGHT);
		coord_screen[X_AXIS] = 0;
		while (coord_screen[X_AXIS] < WIN_WIDTH)
		{
			cell[X_AXIS] = (int)draw.x_coord;
			cell[Y_AXIS] = (int)draw.y_coord;
			put_texture_floor(&draw, info, coord_screen, cell);
			coord_screen[X_AXIS] += 1;
			draw.x_coord += draw.x_span;
			draw.y_coord += draw.y_span;
		}
		coord_screen[Y_AXIS] += 1;
	}
	return (0);
}

static int	draw_texture_ceil(t_info *info)
{
	int					coord_screen[2];
	int					cell[2];
	t_draw_background	draw;

	coord_screen[Y_AXIS] = (WIN_HEIGHT / 2) - 1;
	while (coord_screen[Y_AXIS] < WIN_HEIGHT)
	{
		set_draw_background(&draw, &info->vars, coord_screen[Y_AXIS]
			- (WIN_HEIGHT / 2), 0.5 * WIN_HEIGHT);
		coord_screen[X_AXIS] = 0;
		while (coord_screen[X_AXIS] < WIN_WIDTH)
		{
			cell[X_AXIS] = (int)draw.x_coord;
			cell[Y_AXIS] = (int)draw.y_coord;
			put_texture_ceil(&draw, info, coord_screen, cell);
			coord_screen[X_AXIS] += 1;
			draw.x_coord += draw.x_span;
			draw.y_coord += draw.y_span;
		}
		coord_screen[Y_AXIS] += 1;
	}
	return (0);
}

void	try_draw_texture_floor_and_ceil(t_info *info)
{
	if (info->texture_list[FLOOR_1].data.img != NULL)
	{
		draw_texture_floor(info);
	}
	if (info->texture_list[CEILING].data.img != NULL)
	{
		draw_texture_ceil(info);
	}
}
