/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_hnoguchi.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:52:51 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/04 15:40:23 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_HNOGUCHI_H
# define RAYCASTING_HNOGUCHI_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <mlx.h>
# include <sys/time.h>

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define GREEN 0x00008000
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define PINK 0x00FFDBED
# define WHEAT 0x00F5DEB3
# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
//キーを押した時の移動距離

// # define X_AXIS true
// # define Y_AXIS false
# define X_AXIS 0
# define Y_AXIS 1

# define MOVE_DISTANCE 0.5
# define ABS(a) ((a) < 0 ? -(a) : (a))

// texture
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define TEXTURE_LIST_SIZE 10

#define FLOOR_1 0
#define FLOOR_2 1
#define CEILING 2
#define SOUTH_WALL 3
#define NORTH_WALL 4
#define EAST_WALL 5
#define WEST_WALL 6

#define TEXTURE_PATH_FLOOR_1 "./srcs/raycasting/xpm/greystone.xpm"
#define TEXTURE_PATH_FLOOR_2 "./srcs/raycasting/xpm/bluestone.xpm"
#define TEXTURE_PATH_CEILING "./srcs/raycasting/xpm/wood.xpm"
#define TEXTURE_PATH_SOUTH_WALL "./srcs/raycasting/xpm/eagle.xpm"
#define TEXTURE_PATH_NORTH_WALL "./srcs/raycasting/xpm/redbrick.xpm"
#define TEXTURE_PATH_EAST_WALL "./srcs/raycasting/xpm/purplestone.xpm"
#define TEXTURE_PATH_WEST_WALL "./srcs/raycasting/xpm/mossy.xpm"

unsigned int	buffer[WIN_HEIGHT][WIN_WIDTH];

int world_map[MAP_WIDTH][MAP_HEIGHT] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1},
  	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
  	{1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1},
  	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1},
  	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1},
  	{1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1},
  	{1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,0,1,1,0,0,0,0,0,1},
  	{1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,1},
  	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1},
  	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
  	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
  	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  	{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1},
  	{1,1,0,0,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,1},
  	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// typedef enum e_color_rgb			t_color_rgb;
typedef struct s_vars				t_vars;
typedef struct s_data				t_data;
typedef struct s_ray				t_ray;
typedef struct s_texture_data		t_texture_data;
typedef struct s_draw_wall			t_draw_wall;
typedef struct s_draw_texture		t_draw_texture;
typedef struct s_draw_background	t_draw_background;

// enum e_color_rgb {
// 	RGB_Red,
// 	RGB_Green,
// 	RGB_Blue,
// 	RGB_White,
// 	RGB_Yellow
// };

struct	s_data {
	void			*img;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
};

// struct	s_texture
struct	s_texture_data {
	t_data	data;
	int		width;
	int		height;
};

struct s_vars
{
	void			*mlx;
	void			*win;
	double			x_position_vector;
	double			y_position_vector;
	double			x_direction;
	double			y_direction;
	double			x_camera_plane;
	double			y_camera_plane;
	int				screen_width;
	int				screen_height;
	t_data			image;
	t_texture_data	texture_list[TEXTURE_LIST_SIZE];
};

struct s_ray {
	double	x_direction;
	double	y_direction;
	int		current_x_in_map;
	int		current_y_in_map;
	double	x_side_distance;
	double	y_side_distance;
	double	x_delta_distance;
	double	y_delta_distance;
};

// struct s_draw
struct s_draw_wall
{
	int		side;
	double	perpendicular_wall_distance;
	int		line_height;
	int		start;
	int		end;
};

struct s_draw_texture
{
	int		list_number;
	double	wall_x;
	int		x_coordinate;
	double	step;
	double	position;
};

struct s_draw_background {
	float	x_move_amount;
	float	y_move_amount;
	float	x_coordinate;
	float	y_coordinate;
};

#endif
