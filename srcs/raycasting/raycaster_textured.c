/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_textured.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/18 19:04:34 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_textured.h"

// TODO: START difference.
// int pitch = 100;
//
// //calculate lowest and highest pixel to fill in current stripe
// int	draw_start;
// int	draw_end;
// 
// draw_start = (-line_height / 2) + (screen_height / 2) + pitch;
// if(draw_start < 0)
// {
// draw_start = 0;
// }
// draw_end = (line_height / 2) + (h / 2) + pitch;
// if(h <= draw_end)
// {
//	draw_end = h - 1;
// }


// texturing calculations
// 1 subtracted from it so that texture 0 can be used!
int texture_number;

texture_number = world_map[ray->current_x_in_map][ray->current_y_in_map] - 1;

// calculate value of wall_x
// where exactly the wall was hit
double	wall_x;

if(side == 0) 
{
    wall_x = vars->y_position_vector + perpendicular_wall_distance * ray->y_direction;
}
else
{
    wall_x = vars->x_position_vector + perpendicular_wall_distance * ray->x_direction;
}

// double	floor(double x);
// 引数x以下で最大の整数値を得る
wall_x -= floor((wallX));

// x coordinate on the texture
int texture_x;

texture_x = (int)(wall_x * (double)texture_width);
if (side == 0 && 0 < ray->x_direction)
{
    texture_x = texture_width - texture_x - 1;
}
if (side == 1 && ray->y_direction < 0)
{
    texture_x = texture_width - texture_x - 1;
}


// 
//       // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
//       // How much to increase the texture coordinate per screen pixel
//       // double step = 1.0 * texHeight / lineHeight;
//       double	step;
//       double	texture_position;
// 	  int		y;
// 
//       step = (1.0 * texture_height) / line_height;
//       // Starting texture coordinate
//       // double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
//       texture_position = (draw_start - pitch - h / 2 + line_height / 2) * step;
// 	  y = draw_start;
//       while (y < draw_end)
// 	  {
// 		  // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
// 		  // int texY = (int)texPos & (texHeight - 1);
// 		  int			texture_y;
// 		  unsigned int	color;
// 
// 		  texture_y = (int)texture_position & (texture_height - 1);
// 		  texture_position += step;
// 		  // Uint32 color = texture[texNum][texHeight * texY + texX];
// 		  color = texture_list[texture_number][texture_height * texture_y + texture_x];
// 		  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 		  /*
// 		   * Because of this, the last bit of one byte will become the first bit of the next byte,
// 		   * and that screws up the color values!
// 		   * So after the bitshift, the first bit of every byte has to be set to zero,
// 		   * and that can be done by binary "AND-ing" the value with the binary value 011111110111111101111111,
// 		   * which is 8355711 in decimal.
// 		   * So the result of this is indeed a darker color.
// 		   */
// 		  if (side == 1)
// 		  {
// 			  color = (color >> 1) & 8355711;
// 		  }
// 		  buffer[y][x] = color;
// 		  y += 1;
// 	  }
// 	}
//     // drawBuffer(buffer[0]);
//     for(int y = 0; y < h; y++)
// 	{
// 		for(int x = 0; x < w; x++)
// 		{
// 			buffer[y][x] = 0; //clear the buffer instead of cls()
// 		}
// 	}
//   }
// }

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

static bool	is_hit_wall(t_ray *ray)
{
	if (0 < world_map[ray->current_x_in_map][ray->current_y_in_map])
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
	if (world_map[ray->current_x_in_map][ray->current_y_in_map] == 1)
	{
		color = RED;
	}
	else if (world_map[ray->current_x_in_map][ray->current_y_in_map] == 2)
	{
		color = GREEN;
	}
	else if (world_map[ray->current_x_in_map][ray->current_y_in_map] == 3)
	{
		color = BLUE;
	}
	else if (world_map[ray->current_x_in_map][ray->current_y_in_map] == 4)
	{
		color = WHITE;
	}
	else
		color = YELLOW;
	//give x and y sides different brightness
	if (side == Y_AXIS)
		color = color / 2;
	return (color);
}

int	calculate_draw_start(int screen_height, int line_height)
{
	int start;
	int pitch;

	pitch = 100;
    start = (-line_height / 2) + (screen_height / 2) + pitch;
	if(start < 0)
	{
		return (0);
	}
	return (start);
}

int	calculate_draw_end(int screen_height, int line_height)
{
	int	end;
	int pitch;

	pitch = 100;
	end = (line_height / 2) + (screen_height / 2) + pitch;
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
	my_mlx_pixel_put_line(&vars->image, x, draw_start, draw_end, color);
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
			vars->x_position_vector -= vars->x_direction * MOVE_DISTANCE;
			printf("press_key[S_KEY_1]\n");
		}
		if((0 < (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 < (int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE)) && (int)(vars->y_position_vector - (vars->y_direction * MOVE_DISTANCE) < MAP_HEIGHT)))
		{
			vars->y_position_vector -= vars->y_direction * MOVE_DISTANCE;
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
	t_vars			vars;
	unsigned int	texture_list[8][TEXTURE_WIDTH * TEXTURE_HEIGHT];
	int				x;
	int				y;
	
	x = 0;
	y = 0;
	while (x < TEXTURE_WIDTH)
	{
		while (y < TEXTURE_HEIGHT)
		{
			int	xor_color;
			int	y_color;
			int	x_y_color;
			
			xor_color = (x * 256 / TEXTURE_WIDTH) ^ (y * 256 / TEXTURE_HEIGHT);
			y_color = y * 256 / TEXTURE_HEIGHT;
			x_y_color = y * 128 / TEXTURE_HEIGHT + x * 128 / TEXTURE_WIDTH;
			texture_list[0][TEXTURE_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEXTURE_WIDTH - y); // flat red texture with black cross
			texture_list[1][TEXTURE_WIDTH * y + x] = x_y_color + 256 * x_y_color + 65536 * x_y_color; // sloped greyscale
			texture_list[2][TEXTURE_WIDTH * y + x] = 256 * x_y_color + 65536 * x_y_color; // sloped yellow gradient
			texture_list[3][TEXTURE_WIDTH * y + x] = xor_color + 256 * xor_color + 65536 * xor_color; // xor greyscale
			texture_list[4][TEXTURE_WIDTH * y + x] = 256 * xor_color; // xor green
			texture_list[5][TEXTURE_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); // red bricks
			texture_list[6][TEXTURE_WIDTH * y + x] = 65536 * y_color; // red gradient
			texture_list[7][TEXTURE_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; // flat grey texture
			y += 1;
		}
		y = 0;
		x += 1;
	}
	initialize_vars(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_action, &vars);
	mlx_loop(vars.mlx);
}
