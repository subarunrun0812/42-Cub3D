/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:52:51 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/08 17:46:43 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <mlx.h>

typedef enum e_color_rgb	t_color_rgb;
typedef struct s_vars		t_vars;
typedef struct	s_data		t_data;

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

struct s_vars
{
	void	*mlx;
	void	*win;
};

struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
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

int	main(void)
{
	// quickcg.cpp
	int		w; // width of the screen
	int		h; // height of the screen

	double	x_position_vector_player;
	double	y_position_vector_player;
	double	x_direction_player;
	double	y_direction_player;
	double	x_camera_plane_player;
	double	y_camera_plane_player;
	double	current_time_frame;
	double	old_time_frame;

	// quickcg.cpp
	// void	screen(int width, int height, bool fullscreen, const std::string& text);
	w = WIN_WIDTH;
	h = WIN_HEIGHT;
	x_position_vector_player = 22;
	y_position_vector_player = 12;
	x_direction_player = -1;
	y_direction_player = 0;
	x_camera_plane_player = 0;
	y_camera_plane_player = 0.66;
	current_time_frame = 0;
	old_time_frame = 0;

	// screen();
	// 画面の設定を行う関数
	// screen(screenWidth, screenHeight, 0, "Raycaster");
	// done();
	t_vars	vars;
	t_data	image;
	vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	image.img = mlx_new_image(vars.mlx, WIN_WIDTH, WIN_HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	// フレーム全体の描画と、毎回入力を読み取るループ。
	// while(!done())
	// {
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
				x_ray_direction = x_direction_player + (x_camera_plane_player * x_current_camera);
				y_ray_direction = y_direction_player + (y_camera_plane_player * x_current_camera);
				x_current_ray_in_map = int(x_position_vector_player);
				y_current_ray_in_map = int(y_position_vector_player);
				x_side_distance = 0;
				y_side_distance = 0;
				// length of ray from one x or y-side to next x or y-side
				// these are derived as:
				// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
				// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      			// which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      			// where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      			// unlike (dirX, dirY) is not 1, however this does not matter, only the
      			// ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      			// stepping further below works. So the values can be computed as below.
      			// Division through zero is prevented, even though technically that's not
      			// needed in C++ with IEEE 754 floating point values.
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
					x_side_distance = (x_position_vector_player - x_current_ray_in_map) * x_delta_distance;
				}
				else
				{
					step_x = 1;
					x_side_distance = (x_current_ray_in_map + 1.0 - x_position_vector_player) * x_delta_distance;
				}
				if(y_ray_direction < 0)
				{
					step_y = -1;
					y_side_distance = (y_position_vector_player - y_current_ray_in_map) * y_delta_distance;
				}
				else
				{
					step_y = 1;
					y_side_distance = (y_current_ray_in_map + 1.0 - y_position_vector_player) * y_delta_distance;
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
				// Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
				// hit to the camera plane. Euclidean to center camera point would give fisheye effect!
				// This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
				// for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
				// because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
				// steps, but we subtract deltaDist once because one step more into the wall was taken above.
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
					my_mlx_pixel_put_line(image, x, draw_start, draw_end, 0xff0000);
				}
				else if (color == RGB_Green)
				{
					my_mlx_pixel_put_line(image, x, draw_start, draw_end, 0xff00);
				}
				else if (color == RGB_Blue)
				{
					my_mlx_pixel_put_line(image, x, draw_start, draw_end, 0xff);
				}
				else if (color == RGB_White)
				{
					my_mlx_pixel_put_line(image, x, draw_start, draw_end, 0xffffff);
				}
				else if (color == RGB_Yellow)
				{
					my_mlx_pixel_put_line(image, x, draw_start, draw_end, 0xffff00);
				}
			}
			// mlx_put_image_to_window(vars.mlx, vars.window, image.img, 0, 0);
			// mlx_loop(vars.mlx);
			// timing for input and FPS counter
			double	current_time_frame;
			double	old_time_frame;

			old_time_frame = current_time_frame;
			current_time_frame = getTicks();
			double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
			print(1.0 / frameTime); //FPS counter
			redraw();
			cls();

    // //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    // readKeys();
    // //move forward if no wall in front of you
    // if(keyDown(SDLK_UP))
    // {
    //   if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if(keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    // }
    // //rotate to the right
    // if(keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if(keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    // }
  // }
}
