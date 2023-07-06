/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_hnoguchi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/06 11:26:46 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_window(t_vars *vars)
{
	if (vars->mlx != NULL && vars->win != NULL)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	}
}

void	destroy_textures(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->mlx == NULL)
	{
		return ;
	}
	while (i < TEXTURE_LIST_SIZE)
	{
		if (vars->texture_list[i].data.img != NULL)
		{
			mlx_destroy_image(vars->mlx, vars->texture_list[i].data.img);
		}
		i += 1;
	}
}

// void	destroy_display(t_vars *vars)
// {
// 	if (vars->mlx != NULL)
// 	{
// 		mlx_destroy_display(vars->mlx);
// 	}
// }

void	destruct_raycasting(t_info *info)
{
	destroy_window(info->vars);
	destroy_textures(info->vars);
	free(info->vars->mlx);
}

// TODO: texture_mlx_pixel_put_line.c
void	texture_mlx_pixel_put_line(t_vars *vars, int x_axis, int y_axis[2],
		unsigned int color)
{
	int				y;
	unsigned int	*dst;

	y = y_axis[0];
	while (y <= y_axis[1])
	{
		dst = vars->data->addr + (y * WIN_WIDTH + x_axis);
		*dst = color;
		y += 1;
	}
}

// TODO: get_nearest_axis.c
static bool	is_hit_wall(char **map, t_ray *ray)
{
	if ('0' < map[ray->current_x_in_map][ray->current_y_in_map]
		&& map[ray->current_x_in_map][ray->current_y_in_map] <= '9')
	{
		return (true);
	}
	return (false);
}

static int	calculate_step_x_direction(t_ray *ray, t_vars *vars)
{
	if (ray->x_direction < 0)
	{
		ray->x_side_distance = (vars->x_position_vector - ray->current_x_in_map)
			* ray->x_delta_distance;
		return (-1);
	}
	ray->x_side_distance = (ray->current_x_in_map + 1.0
			- vars->x_position_vector) * ray->x_delta_distance;
	return (1);
}

static int	calculate_step_y_direction(t_ray *ray, t_vars *vars)
{
	if (ray->y_direction < 0)
	{
		ray->y_side_distance = (vars->y_position_vector - ray->current_y_in_map)
			* ray->y_delta_distance;
		return (-1);
	}
	ray->y_side_distance = (ray->current_y_in_map + 1.0
			- vars->y_position_vector) * ray->y_delta_distance;
	return (1);
}

// perform DDA
int	get_nearest_axis(t_ray *ray, t_info *info)
{
	int	step_x;
	int	step_y;
	int	axis;

	step_x = calculate_step_x_direction(ray, info->vars);
	step_y = calculate_step_y_direction(ray, info->vars);
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
		if (is_hit_wall(info->map->map_data, ray))
			break ;
	}
	return (axis);
}

void	set_draw_background(t_draw_background *draw, t_vars *vars,
		int y_coordinate, float vertical_position_camera)
{
	float	ray_direction_left[2];
	float	ray_direction_right[2];
	float	row_distance;

	ray_direction_left[X_AXIS] = vars->x_direction - vars->x_camera_plane;
	ray_direction_left[Y_AXIS] = vars->y_direction - vars->y_camera_plane;
	ray_direction_right[X_AXIS] = vars->x_direction + vars->x_camera_plane;
	ray_direction_right[Y_AXIS] = vars->y_direction + vars->y_camera_plane;
	row_distance = vertical_position_camera / y_coordinate;
	draw->x_move_amount = row_distance * (ray_direction_right[X_AXIS]
			- ray_direction_left[X_AXIS]) / WIN_WIDTH;
	draw->y_move_amount = row_distance * (ray_direction_right[Y_AXIS]
			- ray_direction_left[Y_AXIS]) / WIN_WIDTH;
	draw->x_coordinate = vars->x_position_vector + row_distance
		* ray_direction_left[X_AXIS];
	draw->y_coordinate = vars->y_position_vector + row_distance
		* ray_direction_left[Y_AXIS];
}

int	decide_texture_floor(int cell[2])
{
	int	checker_board_pattern;

	checker_board_pattern = (int)((cell[X_AXIS] + cell[Y_AXIS]) & 1);
	if (checker_board_pattern == 0)
	{
		return (FLOOR_1);
	}
	return (FLOOR_2);
}

void	put_texture_floor(t_draw_background *draw, t_vars *vars,
		int coordinate_screen[2], int cell[2])
{
	int				coordinate_texture[2];
	int				floor_texture;
	unsigned int	color;

	floor_texture = decide_texture_floor(cell);
	coordinate_texture[X_AXIS] = (int)(vars->texture_list[floor_texture].width
			* (draw->x_coordinate
				- cell[X_AXIS])) & (vars->texture_list[floor_texture].width
			- 1);
	coordinate_texture[Y_AXIS] = (int)(vars->texture_list[floor_texture].height
			* (draw->y_coordinate
				- cell[Y_AXIS])) & (vars->texture_list[floor_texture].height
			- 1);
	color = *(vars->texture_list[floor_texture].data.addr
			+ vars->texture_list[floor_texture].width
			* coordinate_texture[Y_AXIS] + coordinate_texture[X_AXIS]);
	color = (color >> 1) & 8355711;
	vars->data->addr[(WIN_WIDTH * coordinate_screen[Y_AXIS])
		+ coordinate_screen[X_AXIS]] = color;
}

void	put_texture_ceiling(t_draw_background *draw, t_vars *vars,
		int coordinate_screen[2], int cell[2])
{
	int				coordinate_texture[2];
	unsigned int	color;

	coordinate_texture[X_AXIS] = (int)(vars->texture_list[CEILING].width
			* (draw->x_coordinate
				- cell[X_AXIS])) & (vars->texture_list[CEILING].width - 1);
	coordinate_texture[Y_AXIS] = (int)(vars->texture_list[CEILING].height
			* (draw->y_coordinate
				- cell[Y_AXIS])) & (vars->texture_list[CEILING].height - 1);
	color = *(vars->texture_list[CEILING].data.addr
			+ vars->texture_list[CEILING].height * coordinate_texture[Y_AXIS]
			+ coordinate_texture[X_AXIS]);
	color = (color >> 1) & 8355711;
	vars->data->addr[(WIN_WIDTH * (WIN_HEIGHT
				- coordinate_screen[Y_AXIS]))
		+ coordinate_screen[X_AXIS]] = color;
}

unsigned int	create_rgb(int r, int g, int b)
{
	unsigned int	rgb;

	rgb = 0;
	printf("r : [%d]\ng : [%d]\nb : [%d]\n", r, g, b);
	if (r < 0 || 255 < r)
	{
		r = 0;
	}
	if (g < 0 || 255 < g)
	{
		g = 0;
	}
	if (b < 0 || 255 < b)
	{
		b = 0;
	}
	rgb |= (r & 0xFF) << 16;
	rgb |= (g & 0xFF) << 8;
	rgb |= (b & 0xFF);
	return (rgb);
}

int	draw_texture_floor(t_vars *vars)
{
	int					coordinate_screen[2];
	int					cell[2];
	t_draw_background	draw;

	coordinate_screen[Y_AXIS] = (WIN_HEIGHT / 2) - 1;
	while (coordinate_screen[Y_AXIS] < WIN_HEIGHT)
	{
		set_draw_background(&draw, vars,
			coordinate_screen[Y_AXIS] - (WIN_HEIGHT / 2), 0.5 * WIN_HEIGHT);
		coordinate_screen[X_AXIS] = 0;
		while (coordinate_screen[X_AXIS] < WIN_WIDTH)
		{
			cell[X_AXIS] = (int)draw.x_coordinate;
			cell[Y_AXIS] = (int)draw.y_coordinate;
			put_texture_floor(&draw, vars, coordinate_screen, cell);
			coordinate_screen[X_AXIS] += 1;
			draw.x_coordinate += draw.x_move_amount;
			draw.y_coordinate += draw.y_move_amount;
		}
		coordinate_screen[Y_AXIS] += 1;
	}
	return (0);
}

int	draw_texture_ceiling(t_vars *vars)
{
	int					coordinate_screen[2];
	int					cell[2];
	t_draw_background	draw;

	coordinate_screen[Y_AXIS] = (WIN_HEIGHT / 2) - 1;
	while (coordinate_screen[Y_AXIS] < WIN_HEIGHT)
	{
		set_draw_background(&draw, vars, coordinate_screen[Y_AXIS]
			- (WIN_HEIGHT / 2), 0.5 * WIN_HEIGHT);
		coordinate_screen[X_AXIS] = 0;
		while (coordinate_screen[X_AXIS] < WIN_WIDTH)
		{
			cell[X_AXIS] = (int)draw.x_coordinate;
			cell[Y_AXIS] = (int)draw.y_coordinate;
			put_texture_ceiling(&draw, vars, coordinate_screen, cell);
			coordinate_screen[X_AXIS] += 1;
			draw.x_coordinate += draw.x_move_amount;
			draw.y_coordinate += draw.y_move_amount;
		}
		coordinate_screen[Y_AXIS] += 1;
	}
	return (0);
}

void	try_draw_texture_floor_and_ceiling(t_vars *vars)
{
	if (vars->texture_list[FLOOR_1].data.img != NULL)
	{
		draw_texture_floor(vars);
	}
	if (vars->texture_list[CEILING].data.img != NULL)
	{
		draw_texture_ceiling(vars);
	}
}

void	draw_color_floor_and_ceiling(t_vars *vars, unsigned int floor_color
		, unsigned int ceiling_color)
{
	int	x_axis;
	int	y_axis_floor[2];
	int	y_axis_ceiling[2];

	x_axis = 0;
	y_axis_floor[0] = 0;
	y_axis_floor[1] = (WIN_HEIGHT / 2) - 1;
	y_axis_ceiling[0] = y_axis_floor[1];
	y_axis_ceiling[1] = WIN_HEIGHT - 1;
	while (x_axis < WIN_WIDTH)
	{
		texture_mlx_pixel_put_line(vars, x_axis, y_axis_floor, floor_color);
		texture_mlx_pixel_put_line(vars, x_axis, y_axis_ceiling, ceiling_color);
		x_axis += 1;
	}
}

void	set_ray_data(t_ray *ray, t_vars *vars, int x)
{
	double	x_current_camera;

	x_current_camera = 2 * x / (double)WIN_WIDTH - 1;
	ray->x_direction = vars->x_direction + (vars->x_camera_plane
			* x_current_camera);
	ray->y_direction = vars->y_direction + (vars->y_camera_plane
			* x_current_camera);
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

double	get_perpendicular_wall_distance(t_ray *ray, int side)
{
	if (side == X_AXIS)
	{
		return (ray->x_side_distance - ray->x_delta_distance);
	}
	return (ray->y_side_distance - ray->y_delta_distance);
}

int	decide_draw_texture(t_ray *ray, t_vars *vars, int side)
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

int	get_draw_start_y_coordinate(int line_height)
{
	int	start;

	start = (-line_height / 2) + (WIN_HEIGHT / 2);
	if (start < 0)
	{
		return (0);
	}
	return (start);
}

int	get_draw_end_y_coordinate(int line_height)
{
	int	end;

	end = (line_height / 2) + (WIN_HEIGHT / 2);
	if (WIN_HEIGHT <= end)
	{
		return (WIN_HEIGHT - 1);
	}
	return (end);
}

double	get_hit_wall_x(t_draw_wall *wall, t_ray *ray, t_vars *vars)
{
	double	wall_x;

	wall_x = 0.0;
	if (wall->side == X_AXIS)
	{
		wall_x = vars->y_position_vector + wall->perpendicular_wall_distance
			* ray->y_direction;
	}
	else
	{
		wall_x = vars->x_position_vector + wall->perpendicular_wall_distance
			* ray->x_direction;
	}
	wall_x -= floor((wall_x));
	return (wall_x);
}

int	get_x_coordinate_texture(t_draw_texture *texture, t_draw_wall *wall,
		t_ray *ray, t_vars *vars)
{
	int	x_coordinate_texture;

	x_coordinate_texture = (int)(texture->wall_x
			* (double)vars->texture_list[texture->list_number].width);
	if (wall->side == 0 && 0 < ray->x_direction)
	{
		x_coordinate_texture = vars->texture_list[texture->list_number].width
			- x_coordinate_texture - 1;
	}
	if (wall->side == 1 && ray->y_direction < 0)
	{
		x_coordinate_texture = vars->texture_list[texture->list_number].width
			- x_coordinate_texture - 1;
	}
	return (x_coordinate_texture);
}

void	set_draw_wall_data(t_draw_wall *wall, t_ray *ray, t_info *info)
{
	wall->side = get_nearest_axis(ray, info);
	wall->perpendicular_wall_distance
		= get_perpendicular_wall_distance(ray, wall->side);
	wall->line_height = (int)(WIN_HEIGHT
			/ wall->perpendicular_wall_distance);
	wall->start = get_draw_start_y_coordinate(wall->line_height);
	wall->end = get_draw_end_y_coordinate(wall->line_height);
}

void	set_draw_texture_data(t_draw_texture *texture, t_draw_wall *wall,
		t_ray *ray, t_vars *vars)
{
	texture->list_number = decide_draw_texture(ray, vars, wall->side);
	texture->wall_x = get_hit_wall_x(wall, ray, vars);
	texture->x_coordinate = get_x_coordinate_texture(texture, wall, ray, vars);
	texture->step = (1.0 * vars->texture_list[texture->list_number].height)
		/ wall->line_height;
	texture->position = (wall->start - (WIN_HEIGHT / 2)
			+ (wall->line_height / 2)) * texture->step;
}

void	put_texture(t_draw_texture *texture, t_draw_wall *wall, t_vars *vars,
		int x_coordinate_screen)
{
	unsigned int	color;
	int				y_coordinate_screen;
	int				y_coordinate_texture;

	y_coordinate_screen = wall->start;
	while (y_coordinate_screen < wall->end)
	{
		y_coordinate_texture
			= (int)texture->position
			& (vars->texture_list[texture->list_number].height
				- 1);
		texture->position += texture->step;
		color = *(vars->texture_list[texture->list_number].data.addr
				+ vars->texture_list[texture->list_number].height
				* y_coordinate_texture + texture->x_coordinate);
		if (wall->side == Y_AXIS)
		{
			color = (color >> 1) & 8355711;
		}
		vars->data->addr[y_coordinate_screen * WIN_WIDTH
			+ x_coordinate_screen] = color;
		y_coordinate_screen += 1;
	}
}

int	draw_wall(t_info *info)
{
	int				x_coordinate_screen;
	t_ray			ray;
	t_draw_wall		wall;
	t_draw_texture	texture;

	x_coordinate_screen = 0;
	while (x_coordinate_screen < WIN_WIDTH)
	{
		set_ray_data(&ray, info->vars, x_coordinate_screen);
		set_draw_wall_data(&wall, &ray, info);
		set_draw_texture_data(&texture, &wall, &ray, info->vars);
		put_texture(&texture, &wall, info->vars, x_coordinate_screen);
		x_coordinate_screen += 1;
	}
	return (0);
}

// TODO: clean_image.c
void	clean_image(t_vars *vars)
{
	int	x;
	int	y_axis[2];

	x = 0;
	y_axis[0] = 0;
	y_axis[1] = WIN_HEIGHT - 1;
	while (x < WIN_WIDTH)
	{
		texture_mlx_pixel_put_line(vars, x, y_axis, 0x00000000);
		x += 1;
	}
}

// TODO: key_action.c
void	move_forward(char **map, t_vars *vars)
{
	int		one_forward_x_pos_vec;
	int		one_forward_y_pos_vec;
	char	distination;

	one_forward_x_pos_vec = vars->x_position_vector
		+ (vars->x_direction * MOVE_DISTANCE);
	one_forward_y_pos_vec = vars->y_position_vector
		+ (vars->y_direction * MOVE_DISTANCE);
	distination
		= map[one_forward_x_pos_vec][one_forward_y_pos_vec];
	if (distination == '1')
		return ;
	else
	{
		if (0 < one_forward_x_pos_vec && 0 < (int)vars->x_position_vector)
		{
			vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
		}
		if (0 < one_forward_y_pos_vec && 0 < (int)vars->y_position_vector)
		{
			vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
		}
	}
}

// printf("\x1b[33mCrashing into a wall!!!!!\x1b[0m\n");

void	move_backward(char **map, t_vars *vars)
{
	int		one_backward_x_pos_vec;
	int		one_backward_y_pos_vec;
	char	distination;

	one_backward_x_pos_vec
		= vars->x_position_vector - (vars->x_direction * MOVE_DISTANCE);
	one_backward_y_pos_vec
		= vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE);
	distination = map[one_backward_x_pos_vec][one_backward_y_pos_vec];
	if (distination == '1')
		return ;
	else
	{
		if (0 < one_backward_x_pos_vec && 0 < (int)vars->x_position_vector)
			vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
		if (0 < one_backward_y_pos_vec && 0 < (int)vars->y_position_vector)
			vars->y_position_vector -= vars->y_direction * MOVE_DISTANCE;
	}
}

void	rotate_right_camera(t_vars *vars)
{
	double	x_old_direction;
	double	x_old_plane;

	x_old_direction = vars->x_direction;
	x_old_plane = vars->x_camera_plane;
	vars->x_direction = vars->x_direction * cos(-MOVE_DISTANCE)
		- vars->y_direction * sin(-MOVE_DISTANCE);
	vars->y_direction = x_old_direction * sin(-MOVE_DISTANCE)
		+ vars->y_direction * cos(-MOVE_DISTANCE);
	vars->x_camera_plane = vars->x_camera_plane * cos(-MOVE_DISTANCE)
		- vars->y_camera_plane * sin(-MOVE_DISTANCE);
	vars->y_camera_plane = x_old_plane * sin(-MOVE_DISTANCE)
		+ vars->y_camera_plane * cos(-MOVE_DISTANCE);
}

void	rotate_left_camera(t_vars *vars)
{
	double	x_old_direction;
	double	x_old_plane;

	x_old_direction = vars->x_direction;
	x_old_plane = vars->x_camera_plane;
	vars->x_direction = vars->x_direction * cos(MOVE_DISTANCE)
		- vars->y_direction * sin(MOVE_DISTANCE);
	vars->y_direction = x_old_direction * sin(MOVE_DISTANCE) + vars->y_direction
		* cos(MOVE_DISTANCE);
	vars->x_camera_plane = vars->x_camera_plane * cos(MOVE_DISTANCE)
		- vars->y_camera_plane * sin(MOVE_DISTANCE);
	vars->y_camera_plane = x_old_plane * sin(MOVE_DISTANCE)
		+ vars->y_camera_plane * cos(MOVE_DISTANCE);
}

int	key_action(int keycode, t_info *info)
{
	if (keycode == W_KEY || keycode == UP_KEY)
		move_forward(info->map->map_data, info->vars);
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		move_backward(info->map->map_data, info->vars);
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		rotate_right_camera(info->vars);
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		rotate_left_camera(info->vars);
	else if (keycode == ESC_KEY)
		close_window(info);
	else if (keycode == M_KEY)
		info->flag->map *= -1;
	draw_color_floor_and_ceiling(info->vars,
		info->vars->floor_color, info->vars->ceiling_color);
	try_draw_texture_floor_and_ceiling(info->vars);
	draw_wall(info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win,
		info->vars->data->img, 0, 0);
	updata_pos_map(info->vars, info, keycode);
	minimap(info, info->data);
	printf("key_code %d", keycode);
	return (0);
}

// debug_print_mapdata(info);
// printf("map_data[%f][%f]\n", info->vars->x_position_vector,
		// info->vars->y_position_vector);

// TODO: create_xpm_textures.c
void	exit_create_texture(t_info *info,
		char *path, t_texture_data *texture)
{
	texture->data.img
		= mlx_xpm_file_to_image(info->vars->mlx, path,
			&texture->width, &texture->height);
	if (texture->data.img == NULL)
	{
		destruct_raycasting(info);
		print_error("small texture.");
	}
	texture->data.addr
		= (unsigned int *)mlx_get_data_addr(texture->data.img,
			&texture->data.bits_per_pixel,
			&texture->data.line_length,
			&texture->data.endian);
	if (texture->width != 64 || texture->height != 64)
	{
		destruct_raycasting(info);
		print_error("small texture.");
	}
}

void	create_texture_floor(t_info *info,
		char *path, t_texture_data *texture_list)
{
	if (path == NULL)
	{
		texture_list[FLOOR_1].data.img = NULL;
		texture_list[FLOOR_1].data.addr = NULL;
		texture_list[FLOOR_2].data.img = NULL;
		texture_list[FLOOR_2].data.addr = NULL;
		return ;
	}
	exit_create_texture(info, path, &texture_list[FLOOR_1]);
	exit_create_texture(info,
		"./srcs/raycasting/xpm/bluestone.xpm", &texture_list[FLOOR_2]);
}

void	create_texture_ceiling(t_info *info,
		char *path, t_texture_data *texture)
{
	if (path == NULL)
	{
		texture->data.img = NULL;
		texture->data.addr = NULL;
		return ;
	}
	exit_create_texture(info, path, texture);
}

void	initialize_texture_list(t_texture_data *texture_list)
{
	int	i;

	i = 0;
	while (i < TEXTURE_LIST_SIZE)
	{
		texture_list[i].data.img = NULL;
		i += 1;
	}
}

void	create_xpm_textures(t_texture *texture, t_info *info)
{
	initialize_texture_list(info->vars->texture_list);
	create_texture_floor(info, texture->f_tex, info->vars->texture_list);
	create_texture_ceiling(info,
		texture->c_tex, &info->vars->texture_list[CEILING]);
	exit_create_texture(info,
		texture->so, &info->vars->texture_list[SOUTH_WALL]);
	exit_create_texture(info,
		texture->no, &info->vars->texture_list[NORTH_WALL]);
	exit_create_texture(info,
		texture->ea, &info->vars->texture_list[EAST_WALL]);
	exit_create_texture(info,
		texture->we, &info->vars->texture_list[WEST_WALL]);
}

void	set_north_player_direction(t_vars *vars)
{
	vars->x_direction = -1.0;
	vars->y_direction = 0.0;
	vars->x_camera_plane = 0.0;
	vars->y_camera_plane = 0.66;
}

void	set_south_player_direction(t_vars *vars)
{
	vars->x_direction = 1.0;
	vars->y_direction = 0.0;
	vars->x_camera_plane = 0.0;
	vars->y_camera_plane = -0.66;
}

void	set_east_player_direction(t_vars *vars)
{
	vars->x_direction = 0.0;
	vars->y_direction = 1.0;
	vars->x_camera_plane = 0.66;
	vars->y_camera_plane = 0.0;
}

void	set_west_player_direction(t_vars *vars)
{
	vars->x_direction = 0.0;
	vars->y_direction = -1.0;
	vars->x_camera_plane = -0.66;
	vars->y_camera_plane = 0.0;
}

void	init_nswe_dirction(char player_direction, t_vars *vars)
{
	if (player_direction == NORTH)
	{
		set_north_player_direction(vars);
	}
	else if (player_direction == SOUTH)
	{
		set_south_player_direction(vars);
	}
	else if (player_direction == EAST)
	{
		set_east_player_direction(vars);
	}
	else if (player_direction == WEST)
	{
		set_west_player_direction(vars);
	}
}

void	*exit_mlx_init(void)
{
	void	*mlx;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		print_error("Failed malloc.");
	}
	return (mlx);
}

void	*exit_mlx_new_window(void *mlx)
{
	void	*window;

	window = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	if (window == NULL)
	{
		print_error("Failed malloc.");
	}
	return (window);
}

void	*exit_mlx_new_image(void *mlx)
{
	void	*image;

	image = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (image == NULL)
	{
		print_error("Failed malloc.");
	}
	return (image);
}

void	initialize_vars(t_info *info)
{
	info->vars->mlx = exit_mlx_init();
	info->vars->win = exit_mlx_new_window(info->vars->mlx);
	info->vars->x_position_vector = (double)info->map->player_y + 0.500001;
	info->vars->y_position_vector = (double)info->map->player_x + 0.500001;
	init_nswe_dirction
		(info->map->map_data[info->map->player_y][info->map->player_x],
		info->vars);
	info->vars->floor_color
		= create_rgb(info->texture->f_rgb->red,
			info->texture->f_rgb->green, info->texture->f_rgb->blue);
	info->vars->ceiling_color
		= create_rgb(info->texture->c_rgb->red,
			info->texture->c_rgb->green, info->texture->c_rgb->blue);
	info->vars->data->img = exit_mlx_new_image(info->vars->mlx);
	info->vars->data->addr
		= (unsigned int *)mlx_get_data_addr(info->vars->data->img,
			&info->vars->data->bits_per_pixel,
			&info->vars->data->line_length,
			&info->vars->data->endian);
	clean_image(info->vars);
	create_xpm_textures(info->texture, info);
	draw_color_floor_and_ceiling(info->vars,
		info->vars->floor_color, info->vars->ceiling_color);
	try_draw_texture_floor_and_ceiling(info->vars);
	draw_wall(info);
}

// int	close_window(t_info *info)
// {
// 	mlx_loop_end(info->vars->mlx);
// 	return (0);
// }

void	raycasting(t_info *info)
{
	initialize_vars(info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win,
		info->vars->data->img, 0, 0);
	minimap(info, info->data);
	mlx_key_hook(info->vars->win, key_action, info);
	mlx_hook(info->vars->win, ON_DESTROY, 1L<<ON_DESTROY, close_window, info);
	mlx_loop(info->vars->mlx);
	destruct_raycasting(info);
}
