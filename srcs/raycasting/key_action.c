/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/12 14:16:00 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right_camera(t_vars *vars)
{
	double	x_old_dir;
	double	x_old_plane;

	x_old_dir = vars->x_dir;
	x_old_plane = vars->x_cam_plane;
	vars->x_dir = vars->x_dir * cos(-MOVE_DIST)
		- vars->y_dir * sin(-MOVE_DIST);
	vars->y_dir = x_old_dir * sin(-MOVE_DIST)
		+ vars->y_dir * cos(-MOVE_DIST);
	vars->x_cam_plane = vars->x_cam_plane * cos(-MOVE_DIST)
		- vars->y_cam_plane * sin(-MOVE_DIST);
	vars->y_cam_plane = x_old_plane * sin(-MOVE_DIST)
		+ vars->y_cam_plane * cos(-MOVE_DIST);
}

void	rotate_left_camera(t_vars *vars)
{
	double	x_old_dir;
	double	x_old_plane;

	x_old_dir = vars->x_dir;
	x_old_plane = vars->x_cam_plane;
	vars->x_dir = vars->x_dir * cos(MOVE_DIST)
		- vars->y_dir * sin(MOVE_DIST);
	vars->y_dir = x_old_dir * sin(MOVE_DIST) + vars->y_dir
		* cos(MOVE_DIST);
	vars->x_cam_plane = vars->x_cam_plane * cos(MOVE_DIST)
		- vars->y_cam_plane * sin(MOVE_DIST);
	vars->y_cam_plane = x_old_plane * sin(MOVE_DIST)
		+ vars->y_cam_plane * cos(MOVE_DIST);
}

void	re_draw_window(int keycode, t_info *info)
{
	draw_color_floor_and_ceil(&info->data,
		info->vars.floor_col, info->vars.ceil_col);
	try_draw_texture_floor_and_ceil(info);
	draw_wall(info);
	mlx_put_image_to_window(info->vars.mlx, info->vars.win,
		info->data.img, 0, 0);
	updata_pos_map(&info->vars, info, keycode);
	minimap(info, &info->data);
}

int	key_action(int keycode, t_info *info)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		move_forward(info->map.map_data, &info->vars);
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		move_backward(info->map.map_data, &info->vars);
	else if (keycode == D_KEY)
		move_right(info->map.map_data, &info->vars);
	else if (keycode == A_KEY)
		move_left(info->map.map_data, &info->vars);
	else if (keycode == RIGHT_KEY)
		rotate_right_camera(&info->vars);
	else if (keycode == LEFT_KEY)
		rotate_left_camera(&info->vars);
	else if (keycode == ESC_KEY)
		close_window(info);
	else if (keycode == M_KEY)
		info->flag.map *= -1;
	else
		return (-1);
	re_draw_window(keycode, info);
	return (0);
}
