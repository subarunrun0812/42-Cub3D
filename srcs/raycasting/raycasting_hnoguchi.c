/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_hnoguchi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/02 16:06:54 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting_hnoguchi.h"

static void	my_mlx_pixel_put_line(t_vars *vars
		, int x, int y1, int y2, unsigned int color)
{
	int				y;
	unsigned int	*dst;

	y = y1;
	while (y <= y2)
	{
		dst = vars->image.addr + (y * vars->screen_width + x);
		*dst = color;
		y += 1;
	}
}

// TODO: get_nearest_axis.c
static bool	is_hit_wall(t_ray *ray)
{
	// if ('0' < world_map[ray->current_x_in_map][ray->current_y_in_map] && world_map[ray->current_x_in_map][ray->current_y_in_map] < '9')
	if (0 < world_map[ray->current_x_in_map][ray->current_y_in_map])
	{
		return (true);
	}
	return (false);
}

static int	calculate_step_x_direction(t_ray *ray, t_vars *vars)
{
	if (ray->x_direction < 0)
	{
		ray->x_side_distance = (vars->x_position_vector - ray->current_x_in_map) * ray->x_delta_distance;
		return (-1);
	}
	ray->x_side_distance = (ray->current_x_in_map + 1.0 - vars->x_position_vector) * ray->x_delta_distance;
	return (1);
}

static int	calculate_step_y_direction(t_ray *ray, t_vars *vars)
{
	if (ray->y_direction < 0)
	{
		ray->y_side_distance = (vars->y_position_vector - ray->current_y_in_map) * ray->y_delta_distance;
		return (-1);
	}
	ray->y_side_distance = (ray->current_y_in_map + 1.0 - vars->y_position_vector) * ray->y_delta_distance;
	return (1);
}

//perform DDA
bool	get_nearest_axis(t_ray *ray, t_vars *vars)
{
	int		step_x;
	int		step_y;
	bool	axis;

	step_x = calculate_step_x_direction(ray, vars);
	step_y = calculate_step_y_direction(ray, vars);
	while (1)
	{
		if (ray->x_side_distance < ray->y_side_distance)
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

typedef struct s_draw_background	t_draw_background;

struct s_draw_background {
	float	x_move_amount;
	float	y_move_amount;
	float	x_coordinate;
	float	y_coordinate;
};

void	set_draw_data_background(t_draw_background *draw, t_vars *vars, int y_coordinate, float vertical_position_camera)
{
	float	ray_direction_left[2];
	float	ray_direction_right[2];
	float	row_distance;

	ray_direction_left[X] = vars->x_direction - vars->x_camera_plane;
	ray_direction_left[Y] = vars->y_direction - vars->y_camera_plane;
	ray_direction_right[X] = vars->x_direction + vars->x_camera_plane;
	ray_direction_right[Y] = vars->y_direction + vars->y_camera_plane;
	row_distance = vertical_position_camera / y_coordinate;
	draw->x_move_amount = row_distance * (ray_direction_right[X] - ray_direction_left[X]) / vars->screen_width;
	draw->y_move_amount = row_distance * (ray_direction_right[Y] - ray_direction_left[Y]) / vars->screen_width;
	draw->x_coordinate = vars->x_position_vector + row_distance * ray_direction_left[X];
	draw->y_coordinate = vars->y_position_vector + row_distance * ray_direction_left[Y];
}

int	decide_texture_floor(int cell[2])
{
	int	checker_board_pattern;

	checker_board_pattern = (int)((cell[X] + cell[Y]) & 1);
	if (checker_board_pattern == 0)
	{
		return (FLOOR_1);
	}
	return (FLOOR_2);
}

void	put_texture_floor(t_draw_background *draw, t_vars *vars, int coordinate_screen[2], int cell[2])
{
	int				coordinate_texture[2];
	int				floor_texture;
	unsigned int	color;

	floor_texture = decide_texture_floor(cell);
	coordinate_texture[X] = (int)(vars->texture_list[floor_texture].width * (draw->x_coordinate - cell[X])) & (vars->texture_list[floor_texture].width - 1);
	coordinate_texture[Y] = (int)(vars->texture_list[floor_texture].height * (draw->y_coordinate - cell[Y])) & (vars->texture_list[floor_texture].height - 1);
	color = *(vars->texture_list[floor_texture].data.addr + vars->texture_list[floor_texture].width * coordinate_texture[Y] + coordinate_texture[X]);
	color = (color >> 1) & 8355711;
	vars->image.addr[(vars->screen_width * coordinate_screen[Y]) + coordinate_screen[X]] = color;
}

void	put_texture_ceiling(t_draw_background *draw, t_vars *vars, int coordinate_screen[2], int cell[2])
{
	int				coordinate_texture[2];
	unsigned int	color;

	coordinate_texture[X] = (int)(vars->texture_list[CEILING].width * (draw->x_coordinate - cell[X])) & (vars->texture_list[CEILING].width - 1);
	coordinate_texture[Y] = (int)(vars->texture_list[CEILING].height * (draw->y_coordinate - cell[Y])) & (vars->texture_list[CEILING].height - 1);
	color = *(vars->texture_list[CEILING].data.addr + vars->texture_list[CEILING].height * coordinate_texture[Y] + coordinate_texture[X]);
	color = (color >> 1) & 8355711;
	vars->image.addr[(vars->screen_width * (vars->screen_height - coordinate_screen[Y])) + coordinate_screen[X]] = color;
}

int	draw_floor_and_ceiling(t_vars *vars)
{
	int					coordinate_screen[2];
	int					cell[2];
	t_draw_background	draw;

	coordinate_screen[Y] = (vars->screen_height / 2) - 1;
	while (coordinate_screen[Y] < vars->screen_height)
	{
		set_draw_data_background(&draw, vars, coordinate_screen[Y] - (vars->screen_height / 2), 0.5 * vars->screen_height);
		coordinate_screen[X] = 0;
		while (coordinate_screen[X] < vars->screen_width)
		{
			cell[X] = (int)draw.x_coordinate;
			cell[Y] = (int)draw.y_coordinate;
			put_texture_floor(&draw, vars, coordinate_screen, cell);
			put_texture_ceiling(&draw, vars, coordinate_screen, cell);
			coordinate_screen[X] += 1;
			draw.x_coordinate += draw.x_move_amount;
			draw.y_coordinate += draw.y_move_amount;
		}
		coordinate_screen[Y] += 1;
	}
	return (0);
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
	if (ray->x_direction == 0)
	{
		ray->x_delta_distance = 1e30;
	}
	else
		ray->x_delta_distance = ABS(1 / ray->x_direction);
	if (ray->y_direction == 0)
	{
		ray->y_delta_distance = 1e30;
	}
	else
		ray->y_delta_distance = ABS(1 / ray->y_direction);
}

double	get_perpendicular_wall_distance(t_ray *ray, bool side)
{
	if (side == X_AXIS)
	{
		return (ray->x_side_distance - ray->x_delta_distance);
	}
	return (ray->y_side_distance - ray->y_delta_distance);
}

int	decide_draw_texture(t_ray *ray, t_vars *vars, bool side)
{
	if (side == Y_AXIS)
	{
		if (ray->current_y_in_map < vars->y_position_vector)
		{
			return (WEST_WALL);
		}
		return (EAST_WALL);
	}
	else if (ray->current_x_in_map < vars->x_position_vector)
	{
		return (NORTH_WALL);
	}
	return (SOUTH_WALL);
}

int	get_draw_start_y_coordinate(int screen_height, int line_height)
{
	int	start;

	start = (-line_height / 2) + (screen_height / 2);
	if (start < 0)
	{
		return (0);
	}
	return (start);
}

int	get_draw_end_y_coordinate(int screen_height, int line_height)
{
	int	end;

	end = (line_height / 2) + (screen_height / 2);
	if (screen_height <= end)
	{
		return (screen_height - 1);
	}
	return (end);
}

double	get_hit_wall_x(t_draw *draw, t_ray *ray, t_vars *vars)
{
	double	wall_x;

	wall_x = 0.0;
	if (draw->side == X_AXIS)
	{
		wall_x = vars->y_position_vector + draw->perpendicular_wall_distance * ray->y_direction;
	}
	else
	{
		wall_x = vars->x_position_vector + draw->perpendicular_wall_distance * ray->x_direction;
	}
	wall_x -= floor((wall_x));
	return (wall_x);
}

int	get_x_coordinate_texture(t_draw_texture *texture,
		t_draw *draw, t_ray *ray, t_vars *vars)
{
	int	x_coordinate_texture;

	x_coordinate_texture = (int)(texture->wall_x * (double)vars->texture_list[texture->list_number].width);
	if (draw->side == 0 && 0 < ray->x_direction)
	{
		x_coordinate_texture = vars->texture_list[texture->list_number].width - x_coordinate_texture - 1;
	}
	if (draw->side == 1 && ray->y_direction < 0)
	{
		x_coordinate_texture = vars->texture_list[texture->list_number].width - x_coordinate_texture - 1;
	}
	return (x_coordinate_texture);
}

void	set_draw_data_wall(t_draw *draw, t_ray *ray, t_vars *vars)
{
	draw->side = get_nearest_axis(ray, vars);
	draw->perpendicular_wall_distance = get_perpendicular_wall_distance(ray, draw->side);
	draw->line_height = (int)(vars->screen_height / draw->perpendicular_wall_distance);
	draw->start = get_draw_start_y_coordinate(vars->screen_height, draw->line_height);
	draw->end = get_draw_end_y_coordinate(vars->screen_height, draw->line_height);
}

void	set_draw_texture_data(t_draw_texture *texture, t_draw *draw, t_ray *ray, t_vars *vars)
{
	texture->list_number = decide_draw_texture(ray, vars, draw->side);
	texture->wall_x = get_hit_wall_x(draw, ray, vars);
	texture->x_coordinate = get_x_coordinate_texture(texture, draw, ray, vars);
	texture->step = (1.0 * vars->texture_list[texture->list_number].height) / draw->line_height;
	texture->position = (draw->start - (vars->screen_height / 2) + (draw->line_height / 2)) * texture->step;
}

void	put_texture(t_draw_texture *texture, t_draw *draw, t_vars *vars , int x_coordinate_screen)
{
	unsigned int	color;
	int				y_coordinate_screen;
	int				y_coordinate_texture;

	y_coordinate_screen = draw->start;
	while (y_coordinate_screen < draw->end)
	{
		y_coordinate_texture = (int)texture->position & (vars->texture_list[texture->list_number].height - 1);
		texture->position += texture->step;
		color = *(vars->texture_list[texture->list_number].data.addr + vars->texture_list[texture->list_number].height * y_coordinate_texture + texture->x_coordinate);
		if (draw->side == Y_AXIS)
		{
			color = (color >> 1) & 8355711;
		}
		vars->image.addr[y_coordinate_screen * vars->screen_width + x_coordinate_screen] = color;
		y_coordinate_screen += 1;
	}
}

int	draw_image(t_vars *vars)
{
	int				x_coordinate_screen;
	t_ray			ray;
	t_draw			draw;
	t_draw_texture	texture;

	x_coordinate_screen = 0;
	while (x_coordinate_screen < vars->screen_width)
	{
		set_ray_data(&ray, vars, x_coordinate_screen);
		set_draw_data_wall(&draw, &ray, vars);
		set_draw_texture_data(&texture, &draw, &ray, vars);
		put_texture(&texture, &draw, vars, x_coordinate_screen);
		x_coordinate_screen += 1;
	}
	return (0);
}

// TODO: clean_image.c
void	clean_image(t_vars *vars)
{
	int	x;

	x = 0;
	while (x < vars->screen_width)
	{
		my_mlx_pixel_put_line(vars, x, 0, WIN_HEIGHT, 0x00000000);
		x += 1;
	}
}

// TODO: key_action.c
void	move_forward(t_vars *vars)
{
	int	one_step_forward_x_position_vector;
	int	one_step_forward_y_position_vector;

	one_step_forward_x_position_vector = (int)(vars->x_position_vector + vars->x_direction * MOVE_DISTANCE);
	one_step_forward_y_position_vector = (int)(vars->y_position_vector + vars->y_direction * MOVE_DISTANCE);
	// if ((0 < one_step_forward_x_position_vector && one_step_forward_x_position_vector < MAP_WIDTH) && (0 < (int)(vars->y_position_vector) && (int)(vars->y_position_vector) < MAP_HEIGHT))
	if (0 < one_step_forward_x_position_vector && 0 < (int)vars->y_position_vector)
	{
		if (world_map[one_step_forward_x_position_vector][(int)vars->y_position_vector] == 0)
		{
			vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
		}
	}
	// if ((0 < (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 < one_step_forward_y_position_vector && one_step_forward_y_position_vector < MAP_HEIGHT))
	if (0 < (int)(vars->x_position_vector) && 0 < one_step_forward_y_position_vector)
	{
		if (world_map[(int)vars->x_position_vector][one_step_forward_y_position_vector] == 0)
		{
			vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
		}
	}
}

void	move_backward(t_vars *vars)
{
	int	one_step_backward_x_position_vector;
	int	one_step_backward_y_position_vector;

	one_step_backward_x_position_vector = (int)(vars->x_position_vector - vars->x_direction * MOVE_DISTANCE);
	one_step_backward_y_position_vector = (int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE));
	// if ((0 < one_step_backward_x_position_vector && one_step_backward_x_position_vector < MAP_WIDTH) && (0 < (int)(vars->y_position_vector) && (int)(vars->y_position_vector) < MAP_HEIGHT))
	if (0 < one_step_backward_x_position_vector && 0 < (int)vars->y_position_vector)
	{
		if (world_map[one_step_backward_x_position_vector][(int)vars->y_position_vector] == 0)
		{
			vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
		}
	}
	// if ((0 < (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 < one_step_backward_y_position_vector && one_step_backward_y_position_vector < MAP_HEIGHT))
	if (0 < (int)vars->x_position_vector && 0 < one_step_backward_y_position_vector)
	{
		if (world_map[(int)vars->x_position_vector][one_step_backward_y_position_vector] == 0)
		{
			vars->y_position_vector -= vars->y_direction * MOVE_DISTANCE;
		}
	}
}

void	rotate_right_camera(t_vars *vars)
{
	double	x_old_direction;
	double	x_old_plane;

	x_old_direction = vars->x_direction;
	x_old_plane = vars->x_camera_plane;
	vars->x_direction = vars->x_direction * cos(-MOVE_DISTANCE) - vars->y_direction * sin(-MOVE_DISTANCE);
	vars->y_direction = x_old_direction * sin(-MOVE_DISTANCE) + vars->y_direction * cos(-MOVE_DISTANCE);
	vars->x_camera_plane = vars->x_camera_plane * cos(-MOVE_DISTANCE) - vars->y_camera_plane * sin(-MOVE_DISTANCE);
	vars->y_camera_plane = x_old_plane * sin(-MOVE_DISTANCE) + vars->y_camera_plane * cos(-MOVE_DISTANCE);
}

void	rotate_left_camera(t_vars *vars)
{
	double	x_old_direction;
	double	x_old_plane;

	x_old_direction = vars->x_direction;
	x_old_plane = vars->x_camera_plane;
	vars->x_direction = vars->x_direction * cos(MOVE_DISTANCE) - vars->y_direction * sin(MOVE_DISTANCE);
	vars->y_direction = x_old_direction * sin(MOVE_DISTANCE) + vars->y_direction * cos(MOVE_DISTANCE);
	vars->x_camera_plane = vars->x_camera_plane * cos(MOVE_DISTANCE) - vars->y_camera_plane * sin(MOVE_DISTANCE);
	vars->y_camera_plane = x_old_plane * sin(MOVE_DISTANCE) + vars->y_camera_plane * cos(MOVE_DISTANCE);
}

int	key_action(int keycode, t_vars *vars)
{
	if (keycode == W_KEY || keycode == UP_KEY)
	{
		move_forward(vars);
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		move_backward(vars);
	}
	else if(keycode == D_KEY || keycode == RIGHT_KEY)
	{
		rotate_right_camera(vars);
	}
	else if(keycode == A_KEY || keycode == LEFT_KEY)
	{
		rotate_left_camera(vars);
	}
	// else if (keycode == ESC_KEY)
	// {
	// 	close_window(info);
	// }
	// else if (keycode == M_KEY)
	// {
	// 	info->flag->map *= -1;
	// }
	draw_floor_and_ceiling(vars);
	draw_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	//minimapの再描画
	// minimap(info, info->data);
	clean_image(vars);
	return (0);
}

// TODO: create_xpm_textures.c
void	create_floor_textures(t_vars *vars)
{
	vars->texture_list[FLOOR_1].data.img = mlx_xpm_file_to_image(vars->mlx,
			TEXTURE_PATH_FLOOR_1,
			&vars->texture_list[FLOOR_1].width,
			&vars->texture_list[FLOOR_1].height);
	vars->texture_list[FLOOR_1].data.addr = (unsigned int *)mlx_get_data_addr(
			vars->texture_list[FLOOR_1].data.img,
			&vars->texture_list[FLOOR_1].data.bits_per_pixel,
			&vars->texture_list[FLOOR_1].data.line_length,
			&vars->texture_list[FLOOR_1].data.endian);
	vars->texture_list[FLOOR_2].data.img = mlx_xpm_file_to_image(vars->mlx,
			TEXTURE_PATH_FLOOR_2,
			&vars->texture_list[FLOOR_2].width,
			&vars->texture_list[FLOOR_2].height);
	vars->texture_list[FLOOR_2].data.addr = (unsigned int *)mlx_get_data_addr(
			vars->texture_list[FLOOR_2].data.img,
			&vars->texture_list[FLOOR_2].data.bits_per_pixel,
			&vars->texture_list[FLOOR_2].data.line_length,
			&vars->texture_list[FLOOR_2].data.endian);
}

void	create_ceiling_textures(t_vars *vars)
{
	vars->texture_list[CEILING].data.img = mlx_xpm_file_to_image(
			vars->mlx, TEXTURE_PATH_CEILING,
			&vars->texture_list[CEILING].width,
			&vars->texture_list[CEILING].height);
	vars->texture_list[CEILING].data.addr = (unsigned int *)mlx_get_data_addr(
			vars->texture_list[CEILING].data.img,
			&vars->texture_list[CEILING].data.bits_per_pixel,
			&vars->texture_list[CEILING].data.line_length,
			&vars->texture_list[CEILING].data.endian);
}

void	create_south_and_north_textures(t_vars *vars)
{
	vars->texture_list[SOUTH_WALL].data.img
		= mlx_xpm_file_to_image(
			vars->mlx, TEXTURE_PATH_SOUTH_WALL,
			&vars->texture_list[SOUTH_WALL].width,
			&vars->texture_list[SOUTH_WALL].height);
	vars->texture_list[SOUTH_WALL].data.addr
		= (unsigned int *)mlx_get_data_addr(
			vars->texture_list[SOUTH_WALL].data.img,
			&vars->texture_list[SOUTH_WALL].data.bits_per_pixel,
			&vars->texture_list[SOUTH_WALL].data.line_length,
			&vars->texture_list[SOUTH_WALL].data.endian);
	vars->texture_list[NORTH_WALL].data.img
		= mlx_xpm_file_to_image(
			vars->mlx, TEXTURE_PATH_NORTH_WALL,
			&vars->texture_list[NORTH_WALL].width,
			&vars->texture_list[NORTH_WALL].height);
	vars->texture_list[NORTH_WALL].data.addr
		= (unsigned int *)mlx_get_data_addr(
			vars->texture_list[NORTH_WALL].data.img,
			&vars->texture_list[NORTH_WALL].data.bits_per_pixel,
			&vars->texture_list[NORTH_WALL].data.line_length,
			&vars->texture_list[NORTH_WALL].data.endian);
}

void	create_east_and_west_textures(t_vars *vars)
{
	vars->texture_list[EAST_WALL].data.img = mlx_xpm_file_to_image(
			vars->mlx, TEXTURE_PATH_EAST_WALL,
			&vars->texture_list[EAST_WALL].width,
			&vars->texture_list[EAST_WALL].height);
	vars->texture_list[EAST_WALL].data.addr = (unsigned int *)mlx_get_data_addr(
			vars->texture_list[EAST_WALL].data.img,
			&vars->texture_list[EAST_WALL].data.bits_per_pixel,
			&vars->texture_list[EAST_WALL].data.line_length,
			&vars->texture_list[EAST_WALL].data.endian);
	vars->texture_list[WEST_WALL].data.img = mlx_xpm_file_to_image(
			vars->mlx,
			TEXTURE_PATH_WEST_WALL,
			&vars->texture_list[WEST_WALL].width,
			&vars->texture_list[WEST_WALL].height);
	vars->texture_list[WEST_WALL].data.addr = (unsigned int *)mlx_get_data_addr(
			vars->texture_list[WEST_WALL].data.img,
			&vars->texture_list[WEST_WALL].data.bits_per_pixel,
			&vars->texture_list[WEST_WALL].data.line_length,
			&vars->texture_list[WEST_WALL].data.endian);
}

void	create_xpm_textures(t_vars *vars)
{
	create_floor_textures(vars);
	create_ceiling_textures(vars);
	create_south_and_north_textures(vars);
	create_east_and_west_textures(vars);
}

// North
// vars->x_direction = -1.0;
// vars->y_direction = 0.0;
// vars->x_camera_plane = 0.0;
// vars->y_camera_plane = 0.66;

// South
// vars->x_direction = 1.0;
// vars->y_direction = 0.0;
// vars->x_camera_plane = 0.0;
// vars->y_camera_plane = -0.66;

// West
// vars->x_direction = 0.0;
// vars->y_direction = -1.0;
// vars->x_camera_plane = -0.66;
// vars->y_camera_plane = 0.0;

// East
// vars->x_direction = 0.0;
// vars->y_direction = 1.0;
// vars->x_camera_plane = 0.66;
// vars->y_camera_plane = 0.0;

// TODO: initialize_vars.c
void	initialize_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	vars->x_position_vector = 22.0;
	vars->y_position_vector = 11.5;
	vars->x_direction = -1.0;
	vars->y_direction = 0.0;
	vars->x_camera_plane = 0.0;
	vars->y_camera_plane = 0.66;
	vars->screen_width = WIN_WIDTH;
	vars->screen_height = WIN_HEIGHT;
	vars->image.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image.addr = (unsigned int *)mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, &vars->image.line_length, &vars->image.endian);
	create_xpm_textures(vars);
	draw_floor_and_ceiling(vars);
	draw_image(vars);
}

int	main(void)
{
	t_vars			vars;

	initialize_vars(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_action, &vars);
	mlx_loop(vars.mlx);
}
