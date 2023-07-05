/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_hnoguchi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/05 16:03:07 by hnoguchi         ###   ########.fr       */
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

void	end_raycasting(t_info *info)
{
	destroy_window(info->vars);
	destroy_textures(info->vars);
	// destroy_display(info->vars);
	free(info->vars->mlx);
}

static void	texture_mlx_pixel_put_line(t_vars *vars, int x, int y1, int y2,
		unsigned int color)
{
	int				y;
	unsigned int	*dst;

	y = y1;
	while (y <= y2)
	{
		dst = vars->data->addr + (y * WIN_WIDTH + x);
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
		set_draw_background(&draw, vars, coordinate_screen[Y_AXIS]
				- (WIN_HEIGHT / 2), 0.5 * WIN_HEIGHT);
		coordinate_screen[X_AXIS] = 0;
		while (coordinate_screen[X_AXIS] < WIN_WIDTH)
		{
			cell[X_AXIS] = (int)draw.x_coordinate;
			cell[Y_AXIS] = (int)draw.y_coordinate;
			put_texture_floor(&draw, vars, coordinate_screen, cell);
			// put_texture_ceiling(&draw, vars, coordinate_screen, cell);
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
			// put_texture_floor(&draw, vars, coordinate_screen, cell);
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

void	draw_color_floor_and_ceiling(t_vars *vars, unsigned int floor_color, unsigned int ceiling_color)
{
	int	x_axis;
	int	y_axis_center;

	x_axis = 0;
	y_axis_center = (WIN_HEIGHT / 2) - 1;
	while (x_axis < WIN_WIDTH)
	{
		texture_mlx_pixel_put_line(vars, x_axis, 0, y_axis_center, floor_color);
		texture_mlx_pixel_put_line(vars, x_axis, (y_axis_center - 1), (WIN_HEIGHT - 1), ceiling_color);
		x_axis += 1;
	}
	printf("floor   : [%d]\n", floor_color);
	printf("ceiling : [%d]\n", ceiling_color);
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
	wall->perpendicular_wall_distance = get_perpendicular_wall_distance(ray,
																		wall->side);
	wall->line_height = (int)(WIN_HEIGHT
			/ wall->perpendicular_wall_distance);
	wall->start = get_draw_start_y_coordinate(WIN_HEIGHT,
												wall->line_height);
	wall->end = get_draw_end_y_coordinate(WIN_HEIGHT,
											wall->line_height);
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
		y_coordinate_texture = (int)texture->position & (vars->texture_list[texture->list_number].height
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

	x = 0;
	while (x < WIN_WIDTH)
	{
		texture_mlx_pixel_put_line(vars, x, 0, (WIN_HEIGHT - 1), 0x00000000);
		x += 1;
	}
}

// TODO: key_action.c
void	move_forward(char **map, t_vars *vars)
{
	int		one_step_forward_x_position_vector;
	int		one_step_forward_y_position_vector;
	char	distination;

	one_step_forward_x_position_vector = vars->x_position_vector
		+ (vars->x_direction * MOVE_DISTANCE);
	one_step_forward_y_position_vector = vars->y_position_vector
		+ (vars->y_direction * MOVE_DISTANCE);
	distination = map[one_step_forward_x_position_vector][one_step_forward_y_position_vector];
	if (distination == '1' || distination == '2' || distination == '3'
		|| distination == '4')
		printf("\x1b[31m壁に衝突!!!!!\x1b[0m\n");
	else
	{
		if (0 < one_step_forward_x_position_vector
			&& 0 < (int)vars->x_position_vector)
		{
			vars->x_position_vector += vars->x_direction * MOVE_DISTANCE;
		}
		if (0 < one_step_forward_y_position_vector
			&& 0 < (int)vars->y_position_vector)
		{
			vars->y_position_vector += vars->y_direction * MOVE_DISTANCE;
		}
	}
}

void	move_backward(char **map, t_vars *vars)
{
	int		one_step_backward_x_position_vector;
	int		one_step_backward_y_position_vector;
	char	distination;

	one_step_backward_x_position_vector = vars->x_position_vector
		- (vars->x_direction * MOVE_DISTANCE);
	one_step_backward_y_position_vector = vars->y_position_vector
		- (vars->y_direction * MOVE_DISTANCE);
	distination = map[one_step_backward_x_position_vector][one_step_backward_y_position_vector];
	if (distination == '1' || distination == '2' || distination == '3'
		|| distination == '4')
		printf("\x1b[31m壁に衝突!!!!!\x1b[0m\n");
	else
	{
		if (0 < one_step_backward_x_position_vector
			&& 0 < (int)vars->x_position_vector)
			vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
		if (0 < one_step_backward_y_position_vector
			&& 0 < (int)vars->y_position_vector)
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
	{
		move_forward(info->map->map_data, info->vars);
	}
	else if (keycode == S_KEY || keycode == DOWN_KEY)
	{
		move_backward(info->map->map_data, info->vars);
	}
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
	{
		rotate_right_camera(info->vars);
	}
	else if (keycode == A_KEY || keycode == LEFT_KEY)
	{
		rotate_left_camera(info->vars);
	}
	else if (keycode == ESC_KEY)
	{
		close_window(info);
	}
	else if (keycode == M_KEY)
	{
		info->flag->map *= -1;
	}
	draw_color_floor_and_ceiling(info->vars, info->vars->floor_color, info->vars->ceiling_color);
	try_draw_texture_floor_and_ceiling(info->vars);
	draw_wall(info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win,
			info->vars->data->img, 0, 0);
	// minimapの再描画
	updata_pos_map(info->vars, info, keycode);
	minimap(info, info->data);
	// debug_print_mapdata(info);
	printf("map_data[%f][%f]\n", info->vars->x_position_vector,
			info->vars->y_position_vector);
	return (0);
}

// TODO: create_xpm_textures.c
void	exit_create_texture(void *mlx, char *path, t_texture_data *texture)
{
	texture->data.img = mlx_xpm_file_to_image(mlx, path, &texture->width, &texture->height);
	if (texture->data.img == NULL)
	{
		texture->data.img = NULL;
		print_error("Failed malloc.");
	}
	texture->data.addr = (unsigned int *)mlx_get_data_addr(texture->data.img, &texture->data.bits_per_pixel, &texture->data.line_length, &texture->data.endian);
}

void	create_texture_floor(void *mlx, char *path, t_texture_data *texture_list)
{
	if (path == NULL)
	{
		texture_list[FLOOR_1].data.img = NULL;
		texture_list[FLOOR_1].data.addr = NULL;
		texture_list[FLOOR_2].data.img = NULL;
		texture_list[FLOOR_2].data.addr = NULL;
		return ;
	}
	exit_create_texture(mlx, path, &texture_list[FLOOR_1]);
	exit_create_texture(mlx, "./srcs/raycasting/xpm/bluestone.xpm", &texture_list[FLOOR_2]);
}

void	create_texture_ceiling(void *mlx, char *path, t_texture_data *texture)
{
	if (path == NULL)
	{
		texture->data.img = NULL;
		texture->data.addr = NULL;
		return ;
	}
	exit_create_texture(mlx, path, texture);
}

void	create_xpm_textures(t_texture *texture, t_vars *vars)
{
	create_texture_floor(vars->mlx, texture->f_tex, vars->texture_list);
	create_texture_ceiling(vars->mlx, texture->c_tex, &vars->texture_list[CEILING]);
	exit_create_texture(vars->mlx, texture->so, &vars->texture_list[SOUTH_WALL]);
	exit_create_texture(vars->mlx, texture->no, &vars->texture_list[NORTH_WALL]);
	exit_create_texture(vars->mlx, texture->ea, &vars->texture_list[EAST_WALL]);
	exit_create_texture(vars->mlx, texture->we, &vars->texture_list[WEST_WALL]);
}

void	init_nswe_dirction(char player_direction, t_vars *vars)
{
	if (player_direction == NORTH)
	{
		vars->x_direction = -1.0;
		vars->y_direction = 0.0;
		vars->x_camera_plane = 0.0;
		vars->y_camera_plane = 0.66;
	}
	else if (player_direction == SOUTH)
	{
		vars->x_direction = 1.0;
		vars->y_direction = 0.0;
		vars->x_camera_plane = 0.0;
		vars->y_camera_plane = -0.66;
	}
	else if (player_direction == EAST)
	{
		vars->x_direction = 0.0;
		vars->y_direction = 1.0;
		vars->x_camera_plane = 0.66;
		vars->y_camera_plane = 0.0;
	}
	else if (player_direction == WEST)
	{
		vars->x_direction = 0.0;
		vars->y_direction = -1.0;
		vars->x_camera_plane = -0.66;
		vars->y_camera_plane = 0.0;
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

// TODO: initialize_vars.c
void	initialize_vars(t_info *info)
{
	info->vars->mlx = exit_mlx_init();
	info->vars->win = exit_mlx_new_window(info->vars->mlx);
	//ゲーム開始時は整数値のためそのまま真っ直ぐに進むと壁がすり抜けて見えてしまうバグがあるため、初期値の値を僅かに増やした。
	info->vars->x_position_vector = (double)info->map->player_y + 0.000001;
	info->vars->y_position_vector = (double)info->map->player_x + 0.000001;
	init_nswe_dirction(info->map->map_data[info->map->player_y][info->map->player_x],
						info->vars);
	//TODO:screen_width,heightを削除する
	//理由:構造体のメンバ変数screen_*にマクロ変数のWIN_*を代入しているため、このメンバ変数を定義する必要はない
	printf("fr : [%d]\n", info->texture->f_rgb->red);
	printf("fg : [%d]\n", info->texture->f_rgb->green);
	printf("fb : [%d]\n", info->texture->f_rgb->blue);
	printf("cr : [%d]\n", info->texture->c_rgb->red);
	printf("cg : [%d]\n", info->texture->c_rgb->green);
	printf("cb : [%d]\n", info->texture->c_rgb->blue);
	info->vars->floor_color = create_rgb(info->texture->f_rgb->red, info->texture->f_rgb->green, info->texture->f_rgb->blue);
	info->vars->ceiling_color = create_rgb(info->texture->c_rgb->red, info->texture->c_rgb->green, info->texture->c_rgb->blue);
	info->vars->data->img = exit_mlx_new_image(info->vars->mlx);
	info->vars->data->addr = (unsigned int *)mlx_get_data_addr(info->vars->data->img, &info->vars->data->bits_per_pixel, &info->vars->data->line_length, &info->vars->data->endian);
	clean_image(info->vars);
	create_xpm_textures(info->texture, info->vars);
	draw_color_floor_and_ceiling(info->vars, info->vars->floor_color, info->vars->ceiling_color);
	try_draw_texture_floor_and_ceiling(info->vars);
	draw_wall(info);
}

void	raycasting(t_info *info)
{
	initialize_vars(info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win,
			info->vars->data->img, 0, 0);
	minimap(info, info->data);
	mlx_key_hook(info->vars->win, key_action, info);
	mlx_loop(info->vars->mlx);
	end_raycasting(info);
}
