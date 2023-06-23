/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:41 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/23 14:50:24 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

void	set_ray_data(t_ray *ray, t_vars *vars, int x)
{
	double	x_current_camera;

	x_current_camera = 2 * x / (double)vars->screen_width - 1;
	ray->x_direction = vars->x_direction + (vars->x_camera_plane * x_current_camera);
	ray->y_direction = vars->y_direction + (vars->y_camera_plane * x_current_camera);
	ray->current_x_in_map = (int)vars->x_position_vector;
	ray->current_y_in_map = (int)vars->y_position_vector;
	ray->x_side_distance = 0;
	ray->y_side_distance = 0;
	// ゼロ除算を回避する。（ゼロの場合は、非常に大きい値を設定する。）
	ray->x_delta_distance = (ray->x_direction == 0) ? 1e30 : ABS(1 / ray->x_direction);
	ray->y_delta_distance = (ray->y_direction == 0) ? 1e30 : ABS(1 / ray->y_direction);
}

int	draw_image(t_vars *vars,t_info *info)
{
	int		x_axis;
	bool	side;
	//レイが当たった壁までの直行距離
	double	perpendicular_wall_distance;
	t_ray	ray;
	
	info->ray = &ray;
	x_axis = 0;
	side = X_AXIS;
	perpendicular_wall_distance = 0;
	while (x_axis < vars->screen_width)
	{
		set_ray_data(&ray, vars, x_axis);
		// printf("\x1b[32mx_axis = %d\x1b[0m\n",x_axis);
		side = calculate_nearest_axis(&ray, vars,info);
		if (side == X_AXIS)
		{
			perpendicular_wall_distance = ray.x_side_distance - ray.x_delta_distance;
		}
		else
		{
			perpendicular_wall_distance = ray.y_side_distance - ray.y_delta_distance;
		}
		draw_line(&ray, info, x_axis, perpendicular_wall_distance, side);
		x_axis += 1;
	}
	return (0);
}

int	key_action(int keycode, t_info *info)
{
	t_vars *vars;
	vars = info->vars;
	// printf("keycode = %d\n",keycode);
	if (keycode == W_KEY || keycode == UP_KEY)
	{
		// 壁衝突の検知
		if (info->map->map_data[(int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE)]
		[(int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE)] == '1' ||
		info->map->map_data[(int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE)]
		[(int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE)] == '2' ||
		info->map->map_data[(int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE)]
		[(int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE)] == '3' ||
		info->map->map_data[(int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE)]
		[(int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE)] == '4')
		{
			printf("\x1b[31m壁に衝突!!!!!\x1b[0m\n");
		}
		else
		{
			if (0 < (int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE))
			{
				vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
				// printf("press_key[W_KEY_1]\n");
			}
			if (0 < (int)(vars->x_position_vector) && (0 < (int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE)))
			{
				vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
				// printf("press_key[W_KEY_2]\n");
			}
		}
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		if(0 < (int)(vars->x_position_vector - vars->x_direction * MOVE_DISTANCE))
		{
			vars->x_direction *= -1;
			vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
			// printf("press_key[S_KEY_1]\n");
		}
		if(0 < (int)(vars->x_position_vector) && (0 < (int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE))))
		{
			vars->y_direction *= -1;
			vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
			// printf("press_key[S_KEY_2]\n");
		}
	}
	else if(keycode == D_KEY || keycode == RIGHT_KEY)
	{
		//both camera direction and camera plane must be rotated
		double	x_old_direction = vars->x_direction;
		vars->x_direction = vars->x_direction * cos(-MOVE_DISTANCE) - vars->y_direction * sin(-MOVE_DISTANCE);
		vars->y_direction = x_old_direction * sin(-MOVE_DISTANCE) + vars->y_direction * cos(-MOVE_DISTANCE);
		double	x_old_plane = vars->x_camera_plane;
		vars->x_camera_plane = vars->x_camera_plane * cos(-MOVE_DISTANCE) - vars->y_camera_plane * sin(-MOVE_DISTANCE);
		vars->y_camera_plane = x_old_plane * sin(-MOVE_DISTANCE) + vars->y_camera_plane * cos(-MOVE_DISTANCE);
		// printf("press_key[D_KEY]\n");
	}
	else if(keycode == A_KEY || keycode == LEFT_KEY)
	{
		//both camera direction and camera plane must be rotated
		double	x_old_direction = vars->x_direction;
		vars->x_direction = vars->x_direction * cos(MOVE_DISTANCE) - vars->y_direction * sin(MOVE_DISTANCE);
		vars->y_direction = x_old_direction * sin(MOVE_DISTANCE) + vars->y_direction * cos(MOVE_DISTANCE);
		double	x_old_plane = vars->x_camera_plane;
		vars->x_camera_plane = vars->x_camera_plane * cos(MOVE_DISTANCE) - vars->y_camera_plane * sin(MOVE_DISTANCE);
		vars->y_camera_plane = x_old_plane * sin(MOVE_DISTANCE) + vars->y_camera_plane * cos(MOVE_DISTANCE);
		// printf("press_key[A_KEY]\n");
	}
	else if (keycode == ESC_KEY)
		close_window(info->vars);
	else if (keycode == M_KEY)
		info->flag->map *= -1;
	// printf("player = %f,%f\n",vars->x_direction,vars->y_direction);
	updata_pos_map(vars, info);
	for(int x = 0; x < vars->screen_width; x++)
	{
		my_mlx_pixel_put_line(vars->image, x, 0, WIN_HEIGHT, 0x00000000);
	}
	draw_image(vars, info);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image->img, 0, 0);
	//minimapの再描画
	minimap(info, info->data);
	return (0);
}

void	initialize_vars(t_vars *vars,t_info *info)
{
	vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");

	// printf("info->player->pos_x=%f\n",info->player->pos_x);
	// printf("info->player->pos_y=%f\n",info->player->pos_y);
	vars->x_position_vector = info->player->pos_y;
	vars->y_position_vector = info->player->pos_x;
	// printf("vars->x_position_vector=%f\n",vars->x_position_vector);
	// printf("vars->y_position_vector=%f\n",vars->y_position_vector);
	vars->x_direction = -1;
	vars->y_direction = 0;

	vars->x_camera_plane = 0;
	vars->y_camera_plane = 0.66;
	vars->screen_width = WIN_WIDTH;
	vars->screen_height = WIN_HEIGHT;

	vars->image->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image->addr = mlx_get_data_addr(vars->image->img, &vars->image->bits_per_pixel, &vars->image->line_length, &vars->image->endian);
	draw_image(vars, info);
	// printf("dir:xy[%f][%f]\n",vars->x_direction,vars->y_direction);
	// printf("player:xy[%f][%f]\n",info->player->pos_x,info->player->pos_y);
	// printf("光線:xy[%d][%d]\n",(int)(info->player->pos_x + (2 * vars->y_direction))\
	// ,(int)(info->player->pos_y + (2 * vars->x_direction)));
	my_mlx_pixel_put(info->data,(int)(info->player->pos_x + (2 * vars->y_direction))\
	,(int)(info->player->pos_y + (2 * vars->x_direction)),BLACK);		
}

int	raycasting(t_info *info)
{
	initialize_vars(info->vars,info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, info->vars->image->img, 0, 0);
	minimap(info, info->data);
	mlx_hook(info->vars->win, ON_DESTROY, 1L << 2, &close_window, info->vars);
	mlx_key_hook(info->vars->win, key_action, info);
	mlx_loop(info->vars->mlx);
	return (0);
}
