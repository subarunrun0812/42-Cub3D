/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 13:53:11 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(char **map, t_vars *vars)
{
	int		one_forward_x_pos_vec;
	int		one_forward_y_pos_vec;
	char	distination;

	one_forward_x_pos_vec = vars->x_pos
		+ (vars->x_dir * MOVE_DIST);
	one_forward_y_pos_vec = vars->y_pos
		+ (vars->y_dir * MOVE_DIST);
	distination
		= map[one_forward_x_pos_vec][one_forward_y_pos_vec];
	if (distination == '1')
		return ;
	else
	{
		if (0 < one_forward_x_pos_vec && 0 < (int)vars->x_pos)
		{
			vars->x_pos += vars->x_dir * MOVE_DIST;
		}
		if (0 < one_forward_y_pos_vec && 0 < (int)vars->y_pos)
		{
			vars->y_pos += vars->y_dir * MOVE_DIST;
		}
	}
}

void	move_backward(char **map, t_vars *vars)
{
	int		one_backward_x_pos_vec;
	int		one_backward_y_pos_vec;
	char	distination;

	one_backward_x_pos_vec
		= vars->x_pos - (vars->x_dir * MOVE_DIST);
	one_backward_y_pos_vec
		= vars->y_pos - (vars->y_dir * MOVE_DIST);
	distination = map[one_backward_x_pos_vec][one_backward_y_pos_vec];
	if (distination == '1')
		return ;
	else
	{
		if (0 < one_backward_x_pos_vec && 0 < (int)vars->x_pos)
			vars->x_pos -= vars->x_dir * MOVE_DIST;
		if (0 < one_backward_y_pos_vec && 0 < (int)vars->y_pos)
			vars->y_pos -= vars->y_dir * MOVE_DIST;
	}
}

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

int	key_action(int keycode, t_info *info)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		move_forward(info->map.map_data, &info->vars);
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		move_backward(info->map.map_data, &info->vars);
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		rotate_right_camera(&info->vars);
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		rotate_left_camera(&info->vars);
	else if (keycode == ESC_KEY)
		close_window(info);
	else if (keycode == M_KEY)
		info->flag.map *= -1;
	else
		return (-1);
	draw_color_floor_and_ceil(&info->data,
		info->vars.floor_col, info->vars.ceil_col);
	try_draw_texture_floor_and_ceil(info);
	draw_wall(info);
	mlx_put_image_to_window(info->vars.mlx, info->vars.win,
		info->data.img, 0, 0);
	updata_pos_map(&info->vars, info, keycode);
	minimap(info, &info->data);
	return (0);
}
