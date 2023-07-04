/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:41 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/04 12:13:21 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//光線の位置と方向を決定する
void	set_ray_data(t_ray *ray, t_vars *vars, int x)
{
	double	x_current_camera;

	// カメラ座標x-1から1の範囲で表したもの
	x_current_camera = 2 * x / (double)vars->screen_width - 1;
	ray->x_direction = vars->x_direction + (vars->x_camera_plane
		* x_current_camera);
	ray->y_direction = vars->y_direction + (vars->y_camera_plane
		* x_current_camera);
	ray->current_x_in_map = (int)vars->x_position_vector;
	ray->current_y_in_map = (int)vars->y_position_vector;
	ray->x_side_distance = 0;
	ray->y_side_distance = 0;
	// ray x,yが次の座標x,yの整数値までの距離を計算する
	// 1e30はゼロ除算を回避する。（ゼロの場合は、非常に大きい値を設定する。）
	ray->x_delta_distance = (ray->x_direction == 0) ? 1e30 : ABS(1
		/ ray->x_direction);
	ray->y_delta_distance = (ray->y_direction == 0) ? 1e30 : ABS(1
		/ ray->y_direction);
}

int	draw_image(t_vars *vars, t_info *info)
{
	int		x_axis;
	bool	side;
	double	perpendicular_wall_distance;
	t_ray	ray;

	//レイが当たった壁までの直行距離
	info->ray = &ray;
	x_axis = 0;
	side = X_AXIS;
	perpendicular_wall_distance = 0;
	while (x_axis < vars->screen_width)
	{
		set_ray_data(&ray, vars, x_axis);
		side = calculate_nearest_axis(&ray, vars, info);
		if (side == X_AXIS)
		{
			perpendicular_wall_distance = ray.x_side_distance
				- ray.x_delta_distance;
		}
		else
		{
			perpendicular_wall_distance = ray.y_side_distance
				- ray.y_delta_distance;
		}
		draw_line(&ray, info, x_axis, perpendicular_wall_distance, side);
		x_axis += 1;
	}
	return (0);
}

void	change_rotate_direction(t_vars *vars, double move_distance)
{
	double	x_old_direction;
	double	x_old_plane;

	x_old_direction = vars->x_direction;
	vars->x_direction = vars->x_direction * cos(move_distance)
		- vars->y_direction * sin(move_distance);
	vars->y_direction = x_old_direction * sin(move_distance) + vars->y_direction
		* cos(move_distance);
	x_old_plane = vars->x_camera_plane;
	vars->x_camera_plane = vars->x_camera_plane * cos(move_distance)
		- vars->y_camera_plane * sin(move_distance);
	vars->y_camera_plane = x_old_plane * sin(move_distance)
		+ vars->y_camera_plane * cos(move_distance);
	printf("\x1b[32mdirection xy=[%f][%f]\x1b[0m\n", vars->x_direction,
		vars->y_direction);
	printf("\x1b[32mcamera_plane xy=[%f][%f]\x1b[0m\n", vars->x_camera_plane,
		vars->y_camera_plane);
}

void	move_forward(t_vars *vars, t_info *info)
{
	char	forward_map_pos;
	vars = info->vars;
	forward_map_pos = info->map->map_data[(int)(vars->x_position_vector
		+ vars->x_direction * MOVE_DISTANCE)][(int)(vars->y_position_vector
		+ vars->y_direction * MOVE_DISTANCE)];
	if (forward_map_pos == '1' || forward_map_pos == '2'
			|| forward_map_pos == '3' || forward_map_pos == '4')
			printf("\x1b[31m壁に衝突!!!!!\x1b[0m\n");
	else
	{
		if (0 < (int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE))
			vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
		if (0 < (int)(vars->x_position_vector) && (0 < (int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE)))
			vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
		}
}

void	move_back(t_vars *vars, t_info *info)
{
	int		map_back_x_pos;
	int		map_back_y_pos;
	char	back_map_pos;

	back_map_pos = info->map->map_data[(int)(vars->x_position_vector
		- vars->x_direction * MOVE_DISTANCE)][(int)(vars->y_position_vector
		- vars->y_direction * MOVE_DISTANCE)];
	map_back_x_pos = (int)(vars->x_position_vector - vars->x_direction
		* MOVE_DISTANCE);
	map_back_y_pos = (int)(vars->y_position_vector - (vars->y_direction
			* MOVE_DISTANCE));
	if (back_map_pos == '1' || back_map_pos == '2' || back_map_pos == '3'
		|| back_map_pos == '4')
		printf("\x1b[31m壁に衝突!!!!!\x1b[0m\n");
	else
	{
		if (0 < map_back_x_pos && (0 < (int)(vars->y_position_vector)))
		{
			vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
		}
		if ((0 < (int)(vars->x_position_vector) && (0 < map_back_y_pos)))
		{
			vars->y_position_vector -= vars->y_direction * MOVE_DISTANCE;
		}
	}
}

int	key_action(int keycode, t_info *info)
{
	t_vars	*vars;

		vars = info->vars;
	if (keycode == W_KEY || keycode == UP_KEY)
	{
		move_forward(vars, info);
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		move_back(vars, info);
	}
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		change_rotate_direction(vars, (MOVE_DISTANCE * -1));
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		change_rotate_direction(vars, MOVE_DISTANCE);
	else if (keycode == ESC_KEY)
		close_window(info);
	else if (keycode == M_KEY)
		info->flag->map *= -1;
	updata_pos_map(vars, info,keycode);
	for (int x = 0; x < vars->screen_width; x++)
		my_mlx_pixel_put_line(vars->image, x, 0, WIN_HEIGHT, 0x00000000);
	draw_image(vars, info);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image->img, 0, 0);
	// minimapの再描画
	minimap(info, info->data);
	return (0);
}

//スタート時のplayerの向きを変更する
void	init_nswe_dirction(t_info *info, t_vars *vars)
{
	if (info->map->map_data[info->map->player_y][info->map->player_x] == NORTH)
		;
	else if (info->map->map_data[info->map->player_y][info->map->player_x] == SOUTH)
		change_rotate_direction(vars, 3.1);
	else if (info->map->map_data[info->map->player_y][info->map->player_x] == EAST)
		change_rotate_direction(vars, -1.55);
	else if (info->map->map_data[info->map->player_y][info->map->player_x] == WEST)
		change_rotate_direction(vars, 1.55);
}

void	initialize_vars(t_vars *vars, t_info *info)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	vars->x_position_vector = info->map->player_y;
	vars->y_position_vector = info->map->player_x;
	vars->x_direction = -1;
	vars->y_direction = 0;
	// camera planeによって、FOVが決まる
	vars->x_camera_plane = 0;
	vars->y_camera_plane = 0.66;
	vars->screen_width = WIN_WIDTH;
	vars->screen_height = WIN_HEIGHT;
	init_nswe_dirction(info, info->vars);
	vars->image->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image->addr = mlx_get_data_addr(vars->image->img,
		&vars->image->bits_per_pixel, &vars->image->line_length,
		&vars->image->endian);
	draw_image(vars, info);
	// my_mlx_pixel_put(info->data, (int)(info->map->player_x + (2
	// 			* vars->y_direction)), (int)(info->map->player_y + (2
	// 			* vars->x_direction)), BLACK);
	// printf("\x1b[32mdirection xy=[%f][%f]\x1b[0m\n",vars->x_direction,vars->y_direction);
	// printf("\x1b[32mcamera_plane xy=[%f][%f]\x1b[0m\n",vars->x_camera_plane,vars->y_camera_plane);
}

int	raycasting(t_info *info)
{
	initialize_vars(info->vars, info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win,
		info->vars->image->img, 0, 0);
	minimap(info, info->data);
	// mlx_hook(info->vars->win, ON_DESTROY, 1L << 2, &close_window, info);
	mlx_key_hook(info->vars->win, key_action, info);
	mlx_loop(info->vars->mlx);
	return (0);
}
