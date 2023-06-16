/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:41 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/16 15:55:25 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"
# include "raycasting.h"

t_info *g_info;


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

// bool	calculate_nearest_axis(t_ray *ray, t_vars *vars);
static bool	is_hit_wall(t_ray *ray)
{
	// 壁に衝突した場合にtrueを返す
	// printf("world_map = %d\n",world_map[ray->current_x_in_map][ray->current_y_in_map]);
	// printf("map_data = %d\n",g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map]);
	if ('0' < g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] &&
	g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] < '9')
	{
		return (true);
	}
	return (false);
}

static int	calculate_step_x_direction(t_ray *ray, t_vars *vars)
{
	if(ray->x_direction < 0)
	{
		ray->x_side_distance = (vars->x_position_vector - ray->current_x_in_map) * ray->x_delta_distance;
		return (-1);
	}
	ray->x_side_distance = (ray->current_x_in_map + 1.0 - vars->x_position_vector) * ray->x_delta_distance;
	return (1);
}

static int	calculate_step_y_direction(t_ray *ray, t_vars *vars)
{
	if(ray->y_direction < 0)
	{
		ray->y_side_distance = (vars->y_position_vector - ray->current_y_in_map) * ray->y_delta_distance;
		return (-1);
	}
	ray->y_side_distance = (ray->current_y_in_map + 1.0 - vars->y_position_vector) * ray->y_delta_distance;
	return (1);
}

//perform DDA
bool	calculate_nearest_axis(t_ray *ray, t_vars *vars)
{
	int		step_x;
	int		step_y;
	bool	axis;

	step_x = calculate_step_x_direction(ray, vars);
	step_y = calculate_step_y_direction(ray, vars);
	while(1)
	{
		if(ray->x_side_distance < ray->y_side_distance)
		{
			ray->x_side_distance += ray->x_delta_distance;
			ray->current_x_in_map += step_x;
			axis = X_AXIS;
		}
		else
		{
			ray->y_side_distance += ray->y_delta_distance;
			ray->current_y_in_map += step_y;
			axis = Y_AXIS;
		}
		if (is_hit_wall(ray))
			break ;
	}
	return (axis);
}

int	decide_color(t_ray *ray, bool side)
{
	int	color;

	color = BLACK;
	if (g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '1')
	{
		color = RED;
	}
	else if (g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '2')
	{
		color = GREEN;
	}
	else if (g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '3')
	{
		color = BLUE;
	}
	else if (g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '4')
	{
		color = WHITE;
	}
	else if (g_info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == 'N')
	{
		;
	}
	else
	{
		color = YELLOW;
	}
	//give x and y sides different brightness
	if (side == Y_AXIS)
		color = color / 2;
	return (color);
}

int	calculate_draw_start(int screen_height, int line_height)
{
	int start;

	start = (-line_height / 2) + (screen_height / 2);
	if(start < 0)
	{
		return (0);
	}
	return (start);
}

int	calculate_draw_end(int screen_height, int line_height)
{
	int	end;

	end = line_height / 2 + screen_height / 2;
	if (screen_height <= end)
	{
		return (screen_height - 1);
	}
	return (end);
}

void	draw_line(t_ray *ray, t_vars *vars, int x, double wall_distance, bool side)
{
	// Calculate height of line to draw on screen
	int	line_height;
	// calculate lowest and highest pixel to fill in current stripe
	int	draw_start;
	int draw_end;
	int	color;

	line_height = (int)(vars->screen_height / wall_distance);
	draw_start = calculate_draw_start(vars->screen_height, line_height);
	draw_end = calculate_draw_end(vars->screen_height, line_height);
	color = decide_color(ray, side);
	my_mlx_pixel_put_line(vars->image, x, draw_start, draw_end, color);
}

int	draw_image(t_vars *vars)
{
	int		x_axis;
	bool	side;
	double	perpendicular_wall_distance;
	t_ray	ray;

	x_axis = 0;
	side = X_AXIS;
	perpendicular_wall_distance = 0;
	while (x_axis < vars->screen_width)
	{
		set_ray_data(&ray, vars, x_axis);
		side = calculate_nearest_axis(&ray, vars);
		if (side == X_AXIS)
		{
			perpendicular_wall_distance = ray.x_side_distance - ray.x_delta_distance;
		}
		else
		{
			perpendicular_wall_distance = ray.y_side_distance - ray.y_delta_distance;
		}
		draw_line(&ray, vars, x_axis, perpendicular_wall_distance, side);
		x_axis += 1;
	}
	return (0);
}

void updata_map(t_vars *vars)
{
	//map情報を更新
	// printf("\x1b[32x=%f,y=%f\x1b[0m\n",vars->x_position_vector,vars->x_position_vector);
	if (g_info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] == '0')
    {
        g_info->map->map_data[(int)(vars->x_position_vector - (vars->x_direction * MOVE_DISTANCE))][(int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE))] = '0';
        g_info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] = 'N';
    }
    else if (g_info->map->map_data[(int)(vars->x_position_vector)][(int)(vars->y_position_vector)] == '1')
    {
        vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
        vars->y_position_vector -= vars->y_direction * MOVE_DISTANCE;
    }
	debug_print_mapdata(g_info);
	
}


int	key_action(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
	{
		if ((0 < (int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE) && (int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE) < MAP_WIDTH) && (0 < (int)(vars->y_position_vector) && (int)(vars->y_position_vector) < MAP_HEIGHT))
		{
			vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
			printf("press_key[W_KEY_1]\n");
		}
		if ((0 < (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 < (int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE) && (int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE) < MAP_HEIGHT))
		{
			vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
			printf("press_key[W_KEY_2]\n");
		}
	}
	else if (keycode == S_KEY)
	{
		if((0 < (int)(vars->x_position_vector - vars->x_direction * MOVE_DISTANCE) && (int)(vars->x_position_vector - vars->x_direction * MOVE_DISTANCE) < MAP_WIDTH) && (0 < (int)(vars->y_position_vector) && (int)(vars->y_position_vector) < MAP_HEIGHT))
		{
			vars->x_direction *= -1;
			vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
			printf("press_key[S_KEY_1]\n");
		}
		if((0 < (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 < (int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE)) && (int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE) < MAP_HEIGHT)))
		{
			vars->y_direction *= -1;
			vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
			printf("press_key[S_KEY_2]\n");
		}
	}
	else if(keycode == D_KEY)
	{
		//both camera direction and camera plane must be rotated
		double	x_old_direction = vars->x_direction;
		vars->x_direction = vars->x_direction * cos(-MOVE_DISTANCE) - vars->y_direction * sin(-MOVE_DISTANCE);
		vars->y_direction = x_old_direction * sin(-MOVE_DISTANCE) + vars->y_direction * cos(-MOVE_DISTANCE);
		double	x_old_plane = vars->x_camera_plane;
		vars->x_camera_plane = vars->x_camera_plane * cos(-MOVE_DISTANCE) - vars->y_camera_plane * sin(-MOVE_DISTANCE);
		vars->y_camera_plane = x_old_plane * sin(-MOVE_DISTANCE) + vars->y_camera_plane * cos(-MOVE_DISTANCE);
		printf("press_key[D_KEY]\n");
	}
	else if(keycode == A_KEY)
	{
		//both camera direction and camera plane must be rotated
		double	x_old_direction = vars->x_direction;
		vars->x_direction = vars->x_direction * cos(MOVE_DISTANCE) - vars->y_direction * sin(MOVE_DISTANCE);
		vars->y_direction = x_old_direction * sin(MOVE_DISTANCE) + vars->y_direction * cos(MOVE_DISTANCE);
		double	x_old_plane = vars->x_camera_plane;
		vars->x_camera_plane = vars->x_camera_plane * cos(MOVE_DISTANCE) - vars->y_camera_plane * sin(MOVE_DISTANCE);
		vars->y_camera_plane = x_old_plane * sin(MOVE_DISTANCE) + vars->y_camera_plane * cos(MOVE_DISTANCE);
		printf("press_key[A_KEY]\n");
	}
	
	updata_map(vars);

	for(int x = 0; x < vars->screen_width; x++)
	{
		my_mlx_pixel_put_line(vars->image, x, 0, WIN_HEIGHT, 0x00000000);
	}
	draw_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image->img, 0, 0);
	return (0);
}

void	initialize_vars(t_vars *vars,t_info *info)
{
	vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");

	// printf("info->player->pos_x=%f\n",info->player->pos_x);
	// printf("info->player->pos_y=%f\n",info->player->pos_y);
	vars->x_position_vector = info->player->pos_x;
	vars->y_position_vector = info->player->pos_y;
	printf("vars->x_position_vector=%f\n",vars->x_position_vector);
	printf("vars->y_position_vector=%f\n",vars->y_position_vector);
	vars->x_direction = -1;
	vars->y_direction = 0;

	// vars->move_speed = MOVE_DISTANCE;
	// vars->rotate_speed = MOVE_DISTANCE;

	vars->x_camera_plane = 0;
	vars->y_camera_plane = 0.66;
	vars->screen_width = WIN_WIDTH;
	vars->screen_height = WIN_HEIGHT;

	vars->image->img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image->addr = mlx_get_data_addr(vars->image->img, &vars->image->bits_per_pixel, &vars->image->line_length, &vars->image->endian);
	draw_image(vars);
}

int	raycasting(t_info *info)
{
	g_info = info;
	initialize_vars(info->vars,info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, info->vars->image->img, 0, 0);
	mlx_key_hook(info->vars->win, key_action, info->vars);
	mlx_loop_hook(info->vars->mlx, draw_image, info->vars);
	mlx_loop(info->vars->mlx);
	return (0);
}
