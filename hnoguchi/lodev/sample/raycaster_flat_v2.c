/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:52:51 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/09 17:22:21 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <mlx.h>
# include <time.h>
# include <sys/time.h>

typedef enum e_color_rgb	t_color_rgb;
typedef struct s_vars		t_vars;
typedef struct	s_data		t_data;

int		w; // width of the screen
int		h; // height of the screen

enum e_color_rgb {
	RGB_Red,
	RGB_Green,
	RGB_Blue,
	RGB_White,
	RGB_Yellow
};

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ABS(a) ((a) < 0 ? -(a) : (a))

int world_map[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_vars
{
	void	*mlx;
	void	*win;
	// key_action
	double	x_position_vector; // posX
	double	y_position_vector; // posY
	double	x_direction; // dirX
	double	y_direction; // dirY
	double move_speed; // moveSpeed
	double rotate_speed; // rotSpeed
	double current_time;
	double	x_camera_plane; // planeX
	double	y_camera_plane; // planeY

	t_data	image;
};

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
	// double	current_time;
 	double	old_time;

	// current_time = 0;
	old_time = 0;
	for(int x = 0; x < w; x++)
	{
		double	x_current_camera;
		double	x_ray_direction;
		double	y_ray_direction;
		int		x_current_ray_in_map;
		int		y_current_ray_in_map;
		double	x_side_distance;
		double	y_side_distance;

		x_current_camera = 2 * x / (double)w - 1;
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
	
		line_height = (int)(h / perpendicular_wall_distance);
		// calculate lowest and highest pixel to fill in current stripe
		int draw_start;
	
		draw_start = -line_height / 2 + h / 2;
		if(draw_start < 0)
		{
			draw_start = 0;
		}
	
		int draw_end;
	
		draw_end = line_height / 2 + h / 2;
		if (draw_end >= h)
		{
			draw_end = h - 1;
		}
		// choose wall color
		t_color_rgb	 color;
		switch(world_map[x_current_ray_in_map][y_current_ray_in_map])
		{
			case 1:
				color = RGB_Red;
				break; //red
			case 2:
				color = RGB_Green;
				break; //green
			case 3:
				color = RGB_Blue;
				break; //blue
			case 4:
				color = RGB_White;
				break; //white
			default:
				color = RGB_Yellow;
				break; //yellow
		}
		//give x and y sides different brightness
		if (side == 1)
		{
			color = color / 2;
		}
		//draw the pixels of the stripe as a vertical line
		if (color == RGB_Red)
		{
			my_mlx_pixel_put_line(&vars->image, x, draw_start, draw_end, 0xff0000);
		}
		else if (color == RGB_Green)
		{
			my_mlx_pixel_put_line(&vars->image, x, draw_start, draw_end, 0xff00);
		}
		else if (color == RGB_Blue)
		{
			my_mlx_pixel_put_line(&vars->image, x, draw_start, draw_end, 0xff);
		}
		else if (color == RGB_White)
		{
			my_mlx_pixel_put_line(&vars->image, x, draw_start, draw_end, 0xffffff);
		}
		else if (color == RGB_Yellow)
		{
			my_mlx_pixel_put_line(&vars->image, x, draw_start, draw_end, 0xffff00);
		}
	}
	old_time = vars->current_time;
	vars->current_time = gettime_millisecond();
	//frameTime is the time this frame has taken, in seconds
	double	frame_time;

	frame_time = (vars->current_time - old_time) / 1000.0;
	vars->move_speed = frame_time * 5.0;
	vars->rotate_speed = frame_time * 3.0;
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
		if ((0 <= (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 <= (int)(vars->y_position_vector + vars->y_direction * vars->move_speed) && (int)(vars->y_position_vector + vars->y_direction * vars->move_speed) < MAP_HEIGHT))
		{
			vars->y_position_vector += vars->y_direction * vars->move_speed;
			printf("press_key[W_KEY_2]\n");
		}
	}
	if (keycode == A_KEY)
	{
		// if(world_map[(int)(vars->x_position_vector - vars->x_direction * vars->move_speed)][(int)(vars->y_position_vector)] == false) vars->x_position_vector -= vars->x_direction * vars->move_speed;
		if((0 <= (int)(vars->x_position_vector - vars->x_direction * vars->move_speed) && (int)(vars->x_position_vector - vars->x_direction * vars->move_speed) < MAP_WIDTH) && (0 <= (int)(vars->y_position_vector) && (int)(vars->y_position_vector) < MAP_HEIGHT))
		{
			vars->x_position_vector -= vars->x_direction * vars->move_speed;
			printf("press_key[A_KEY_1]\n");
		}
		// if(world_map[(int)(vars->x_position_vector)][(int)(vars->y_position_vector - vars->y_direction * vars->move_speed)] == false) vars->y_position_vector -= vars->y_direction * vars->move_speed;
		if((0 <= (int)(vars->x_position_vector) && (int)(vars->x_position_vector) < MAP_WIDTH) && (0 <= (int)(vars->y_position_vector - vars->y_direction * vars->move_speed) && (int)(vars->y_position_vector - vars->y_direction * vars->move_speed) < MAP_HEIGHT))
		{
			vars->y_position_vector -= vars->y_direction * vars->move_speed;
			printf("press_key[A_KEY_2]\n");
		}
	}
	if(keycode == D_KEY)
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
	if(keycode == A_KEY)
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
	draw_image(vars);
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
	vars->image.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, &vars->image.line_length, &vars->image.endian);
	draw_image(vars);
}
int	main(void)
{
	// double	current_time;
	// double	old_time;
	t_vars	vars;

	w = WIN_WIDTH;
	h = WIN_HEIGHT;
	// current_time = 0;
	// old_time = 0;

	initialize_vars(&vars);
	// フレーム全体の描画と、毎回入力を読み取るループ。
	// for(int x = 0; x < w; x++)
	// {
	// 	double	x_current_camera;
	// 	double	x_ray_direction;
	// 	double	y_ray_direction;
	// 	int		x_current_ray_in_map;
	// 	int		y_current_ray_in_map;
	// 	double	x_side_distance;
	// 	double	y_side_distance;

	// 	x_current_camera = 2 * x / (double)w - 1;
	// 	x_ray_direction = vars.x_direction + (vars.x_camera_plane * x_current_camera);
	// 	y_ray_direction = vars.y_direction + (vars.y_camera_plane * x_current_camera);
	// 	x_current_ray_in_map = (int)vars.x_position_vector;
	// 	y_current_ray_in_map = (int)vars.y_position_vector;
	// 	x_side_distance = 0;
	// 	y_side_distance = 0;
	// 	double	x_delta_distance;
	// 	double	y_delta_distance;

	// 	// ¸ゼロ除算を回避する。（ゼロの場合は、非常に大きい値を設定する。）
	// 	x_delta_distance = (x_ray_direction == 0) ? 1e30 : ABS(1 / x_ray_direction);
	// 	y_delta_distance = (y_ray_direction == 0) ? 1e30 : ABS(1 / y_ray_direction);
	// 
	// 	double perpendicular_wall_distance;

	// 	int	step_x;
	// 	int	step_y;
	// 	int hit;
	// 	int side;

	// 	hit = 0;
	// 	if(x_ray_direction < 0)
	// 	{
	// 		step_x = -1;
	// 		x_side_distance = (vars.x_position_vector - x_current_ray_in_map) * x_delta_distance;
	// 	}
	// 	else
	// 	{
	// 		step_x = 1;
	// 		x_side_distance = (x_current_ray_in_map + 1.0 - vars.x_position_vector) * x_delta_distance;
	// 	}
	// 	if(y_ray_direction < 0)
	// 	{
	// 		step_y = -1;
	// 		y_side_distance = (vars.y_position_vector - y_current_ray_in_map) * y_delta_distance;
	// 	}
	// 	else
	// 	{
	// 		step_y = 1;
	// 		y_side_distance = (y_current_ray_in_map + 1.0 - vars.y_position_vector) * y_delta_distance;
	// 	}
	// 	//perform DDA
	// 	while(hit == 0)
	// 	{
	// 		//jump to next map square, either in x-direction, or in y-direction
	// 		if(x_side_distance < y_side_distance)
	// 		{
	// 			x_side_distance += x_delta_distance;
	// 			x_current_ray_in_map += step_x;
	// 			side = 0;
	// 		}
	// 		else
	// 		{
	// 			y_side_distance += y_delta_distance;
	// 			y_current_ray_in_map += step_y;
	// 			side = 1;
	// 		}
	// 		//Check if ray has hit a wall
	// 		if (world_map[x_current_ray_in_map][y_current_ray_in_map] > 0)
	// 		{
	// 			hit = 1;
	// 		}
	// 	}
	// 	if (side == 0)
	// 	{
	// 		perpendicular_wall_distance = (x_side_distance - x_delta_distance);
	// 	}
	// 	else
	// 	{
	// 		perpendicular_wall_distance = (y_side_distance - y_delta_distance);
	// 	}
	// 	//Calculate height of line to draw on screen
	// 	int	line_height;
	// 
	// 	line_height = (int)(h / perpendicular_wall_distance);
	// 	// calculate lowest and highest pixel to fill in current stripe
	// 	int draw_start;
	// 
	// 	draw_start = -line_height / 2 + h / 2;
	// 	if(draw_start < 0)
	// 	{
	// 		draw_start = 0;
	// 	}
	// 	
	// 	int draw_end;
	// 	
	// 	draw_end = line_height / 2 + h / 2;
	// 	if (draw_end >= h)
	// 	{
	// 		draw_end = h - 1;
	// 	}
	// 	// choose wall color
	// 	t_color_rgb	 color;
	// 	switch(world_map[x_current_ray_in_map][y_current_ray_in_map])
	// 	{
	// 		case 1:
	// 			color = RGB_Red;
	// 			break; //red
	// 		case 2:
	// 			color = RGB_Green;
	// 			break; //green
	// 		case 3:
	// 			color = RGB_Blue;
	// 			break; //blue
	// 		case 4:
	// 			color = RGB_White;
	// 			break; //white
	// 		default:
	// 			color = RGB_Yellow;
	// 			break; //yellow
	// 	}
	// 	//give x and y sides different brightness
	// 	if (side == 1)
	// 	{
	// 		color = color / 2;
	// 	}
	// 	//draw the pixels of the stripe as a vertical line
	// 	if (color == RGB_Red)
	// 	{
	// 		my_mlx_pixel_put_line(&vars.image, x, draw_start, draw_end, 0xff0000);
	// 	}
	// 	else if (color == RGB_Green)
	// 	{
	// 		my_mlx_pixel_put_line(&vars.image, x, draw_start, draw_end, 0xff00);
	// 	}
	// 	else if (color == RGB_Blue)
	// 	{
	// 		my_mlx_pixel_put_line(&vars.image, x, draw_start, draw_end, 0xff);
	// 	}
	// 	else if (color == RGB_White)
	// 	{
	// 		my_mlx_pixel_put_line(&vars.image, x, draw_start, draw_end, 0xffffff);
	// 	}
	// 	else if (color == RGB_Yellow)
	// 	{
	// 		my_mlx_pixel_put_line(&vars.image, x, draw_start, draw_end, 0xffff00);
	// 	}
	// }
		// mlx_put_image_to_window(vars.mlx, vars.window, image.img, 0, 0);
		// mlx_loop(vars.mlx);
		// timing for input and FPS counter
		// double	current_time; // time;
		// double	old_time; // oldTime;
		// double	frame_time; // frameTime;

		// old_time = current_time;
		// current_time = gettime_millisecond();
		//frameTime is the time this frame has taken, in seconds
		// double	frame_time;

		// frame_time = (current_time - old_time) / 1000.0;
		// print(1.0 / frameTime); //FPS counter
		// redraw(); // 再描画
		// cls();   // 画面の塗りつぶし

		//speed modifiers
		//the constant value is in squares/second
		// double move_speed; // moveSpeed
		//the constant value is in radians/second
		// double rotate_speed; // rotSpeed

		// vars.move_speed = frame_time * 5.0;
		// vars.rotate_speed = frame_time * 3.0;

		// readKeys();
		mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
		mlx_key_hook(vars.win, key_action, &vars);
		// mlx_loop_hook(vars.mlx, draw_image, &vars);
		mlx_loop(vars.mlx);
}
