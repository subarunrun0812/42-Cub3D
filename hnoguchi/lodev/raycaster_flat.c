/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:52:51 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/11 18:47:04 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raycaster_flat.h"

static void	my_mlx_pixel_put_line(t_data *data, int x, int y1, int y2, int color)
{
	int				y;
	unsigned int	add;
	char			*dst;

	y = y1;
	add = (unsigned int)data->bits_per_pixel / 8;
	while (y <= y2)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
		dst += add;
		y += 1;
	}
}

static double	gettime_millisecond(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((double)(current_time.tv_sec * 1000) + (double)(current_time.tv_usec / 1000));
}

int	draw_image(t_vars *vars)
{
	int		x;
 	double	old_time;

	x = 0;
	old_time = 0;
	while (x < vars->screen_width)
	{
		double	x_current_camera;
		double	x_ray_direction;
		double	y_ray_direction;
		int		x_current_ray_in_map;
		int		y_current_ray_in_map;
		double	x_side_distance;
		double	y_side_distance;

		x_current_camera = 2 * x / (double)vars->screen_width - 1;
		x_ray_direction = vars->x_direction + (vars->x_camera_plane * x_current_camera);
		y_ray_direction = vars->y_direction + (vars->y_camera_plane * x_current_camera);
		x_current_ray_in_map = (int)vars->x_position_vector;
		y_current_ray_in_map = (int)vars->y_position_vector;
		x_side_distance = 0;
		y_side_distance = 0;

		double	x_delta_distance;
		double	y_delta_distance;

		// ¸ゼロ除算を回避する。（ゼロの場合は、非常に大きい値を設定する。）
		x_delta_distance = (x_ray_direction == 0) ? 1e30 : ABS(1 / x_ray_direction);
		y_delta_distance = (y_ray_direction == 0) ? 1e30 : ABS(1 / y_ray_direction);
	
		double perpendicular_wall_distance;

		int	step_x;
		int	step_y;
		int hit;
		int side;

		hit = 0;
		if(x_ray_direction < 0)
		{
			step_x = -1;
			x_side_distance = (vars->x_position_vector - x_current_ray_in_map) * x_delta_distance;
		}
		else
		{
			step_x = 1;
			x_side_distance = (x_current_ray_in_map + 1.0 - vars->x_position_vector) * x_delta_distance;
		}
		if(y_ray_direction < 0)
		{
			step_y = -1;
			y_side_distance = (vars->y_position_vector - y_current_ray_in_map) * y_delta_distance;
		}
		else
		{
			step_y = 1;
			y_side_distance = (y_current_ray_in_map + 1.0 - vars->y_position_vector) * y_delta_distance;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(x_side_distance < y_side_distance)
			{
				x_side_distance += x_delta_distance;
				x_current_ray_in_map += step_x;
				side = 0;
			}
			else
			{
				y_side_distance += y_delta_distance;
				y_current_ray_in_map += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (world_map[x_current_ray_in_map][y_current_ray_in_map] > 0)
			{
				hit = 1;
			}
		}
		if (side == 0)
		{
			perpendicular_wall_distance = (x_side_distance - x_delta_distance);
		}
		else
		{
			perpendicular_wall_distance = (y_side_distance - y_delta_distance);
		}
		//Calculate height of line to draw on screen
		int	line_height;
	
		line_height = (int)(vars->screen_height / perpendicular_wall_distance);
		// calculate lowest and highest pixel to fill in current stripe
		int draw_start;
	
		draw_start = -line_height / 2 + vars->screen_height / 2;
		if(draw_start < 0)
		{
			draw_start = 0;
		}
	
		int draw_end;
	
		draw_end = line_height / 2 + vars->screen_height / 2;
		if (draw_end >= vars->screen_height)
		{
			draw_end = vars->screen_height - 1;
		}
		// choose wall color
		int	color;

		color = BLACK;
		if (world_map[x_current_ray_in_map][y_current_ray_in_map] == 1)
		{
			color = RED;
		}
		else if (world_map[x_current_ray_in_map][y_current_ray_in_map] == 2)
		{
			color = GREEN;
		}
		else if (world_map[x_current_ray_in_map][y_current_ray_in_map] == 3)
		{
			color = BLUE;
		}
		else if (world_map[x_current_ray_in_map][y_current_ray_in_map] == 4)
		{
			color = WHITE;
		}
		else
		{
			color = YELLOW;
		}
		//give x and y sides different brightness
		if (side == 1)
		{
			color = color / 2;
		}
		my_mlx_pixel_put_line(&vars->image, x, draw_start, draw_end, color);
		x += 1;
	}
	old_time = vars->current_time;
	vars->current_time = gettime_millisecond();
	//frameTime is the time this frame has taken, in seconds
	// double	frame_time;

	// frame_time = (vars->current_time - old_time) / 1000.0;
	// vars->move_speed = frame_time * 5.0;
	// vars->rotate_speed = frame_time * 3.0;
	vars->move_speed = MOVE_DISTANCE;
	vars->rotate_speed = MOVE_DISTANCE;
	return (0);
}

int	key_action(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
	{
		if ((0 <= (int)(vars->x_position_vector + vars->x_direction * vars->move_speed) && (int)(vars->x_position_vector + vars->x_direction * vars->move_speed) < MAP_WIDTH) && (0 <= (int)(vars->y_position_vector) && (int)(vars->y_position_vector) < MAP_HEIGHT))
		{
			vars->x_position_vector += vars->x_direction * vars->move_speed;
			printf("press_key[W_KEY_1]\n");
		}
		else if ((0 <= (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 <= (int)(vars->y_position_vector + vars->y_direction * vars->move_speed) && (int)(vars->y_position_vector + vars->y_direction * vars->move_speed) < MAP_HEIGHT))
		{
			vars->y_position_vector += vars->y_direction * vars->move_speed;
			printf("press_key[W_KEY_2]\n");
		}
	}
	else if (keycode == S_KEY)
	{
		if((0 <= (int)(vars->x_position_vector - vars->x_direction * vars->move_speed) && (int)(vars->x_position_vector - vars->x_direction * vars->move_speed) < MAP_WIDTH) && (0 <= (int)(vars->y_position_vector) && (int)(vars->y_position_vector) < MAP_HEIGHT))
		{
			vars->x_position_vector -= vars->x_direction * vars->move_speed;
			printf("press_key[S_KEY_1]\n");
		}
		else if((0 <= (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 <= (int)(vars->y_position_vector - (vars->y_direction * vars->move_speed)) && (int)(vars->y_position_vector - (vars->y_direction * vars->move_speed) < MAP_HEIGHT)))
		{
			vars->y_position_vector -= vars->y_direction * vars->move_speed;
			printf("press_key[S_KEY_2]\n");
		}
	}
	else if(keycode == D_KEY)
	{
		//both camera direction and camera plane must be rotated
		double	x_old_direction = vars->x_direction;
		vars->x_direction = vars->x_direction * cos(-vars->rotate_speed) - vars->y_direction * sin(-vars->rotate_speed);
		vars->y_direction = x_old_direction * sin(-vars->rotate_speed) + vars->y_direction * cos(-vars->rotate_speed);
		double	x_old_plane = vars->x_camera_plane;
		vars->x_camera_plane = vars->x_camera_plane * cos(-vars->rotate_speed) - vars->y_camera_plane * sin(-vars->rotate_speed);
		vars->y_camera_plane = x_old_plane * sin(-vars->rotate_speed) + vars->y_camera_plane * cos(-vars->rotate_speed);
		printf("press_key[D_KEY]\n");
	}
	else if(keycode == A_KEY)
	{
		//both camera direction and camera plane must be rotated
		double	x_old_direction = vars->x_direction;
		vars->x_direction = vars->x_direction * cos(vars->rotate_speed) - vars->y_direction * sin(vars->rotate_speed);
		vars->y_direction = x_old_direction * sin(vars->rotate_speed) + vars->y_direction * cos(vars->rotate_speed);
		double	x_old_plane = vars->x_camera_plane;
		vars->x_camera_plane = vars->x_camera_plane * cos(vars->rotate_speed) - vars->y_camera_plane * sin(vars->rotate_speed);
		vars->y_camera_plane = x_old_plane * sin(vars->rotate_speed) + vars->y_camera_plane * cos(vars->rotate_speed);
		printf("press_key[A_KEY]\n");
	}
	for(int x = 0; x < vars->screen_width; x++)
	{
		my_mlx_pixel_put_line(&vars->image, x, 0, WIN_HEIGHT, 0x00000000);
	}
	draw_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	return (0);
}

void	initialize_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	vars->x_position_vector = 22;
	vars->y_position_vector = 12;
	vars->x_direction = -1;
	vars->y_direction = 0;
	vars->move_speed = 0;
	vars->rotate_speed = 0;
	vars->current_time = gettime_millisecond();
	vars->x_camera_plane = 0;
	vars->y_camera_plane = 0.66;
	vars->screen_width = WIN_WIDTH;
	vars->screen_height = WIN_HEIGHT;
	vars->image.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, &vars->image.line_length, &vars->image.endian);
	draw_image(vars);
}

int	main(void)
{
	t_vars	vars;

	initialize_vars(&vars);
	// readKeys();
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_action, &vars);
	// mlx_loop_hook(vars.mlx, draw_image, &vars);
	mlx_loop(vars.mlx);
}
