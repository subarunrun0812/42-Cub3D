/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:50:22 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 15:49:02 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/get_next_line/get_next_line.h"
# include "../srcs/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

//------------------------------
//			WINDOW
//------------------------------

# define WIN_WIDTH 1200
# define WIN_HEIGHT 600

//------------------------------
//			COLODR
//------------------------------

# define NO_COLOR 0
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define GREEN 0x00008000
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define PINK 0x00FFDBED
# define FUCHSIA 0x00FF00FF
# define MAP_GREEN 0x64008000
# define MAP_WHITE 0x64FFFFFF
# define MAP_PINK 0x64FFDBED
# define MAP_RED 0x64FF0000
# define WHEAT 0x00F5DEB3

//------------------------------
//			KEYCODE
//------------------------------

# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define M_KEY 46
# define ON_DESTROY 17
# define ESC_KEY 53
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
// mouse
# define L_CLICK 1
# define R_CLICK 2

//------------------------------
//			RAYCASTING
//------------------------------

# define X_AXIS true
# define Y_AXIS false

# define X 0
# define Y 1

//キーを押した時の移動距離
# define MOVE_DIST 0.5
// aの絶対値を返す関数
# define ABS(a) ((a) < 0 ? -(a) : (a))

//------------------------------
//			TEXTURE
//------------------------------

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define TEXTURE_LIST_SIZE 10
# define FLOOR_1 0
# define FLOOR_2 1
# define CEILING 2
# define SOUTH_WALL 3
# define NORTH_WALL 4
# define EAST_WALL 5
# define WEST_WALL 6

//------------------------------
//			MINIMAP
//------------------------------

# define BLOCK_SIZE 12
# define DISPLAY_RADIUS 60

//------------------------------
//			OTHER
//------------------------------

# define TRUE 0
# define FALSE 1
# define CORNER 1
# define CENTRAL -1
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

typedef struct s_info	t_info;

extern t_info			*g_info;

typedef struct s_map
{
	char				**map_data;
	int					x_player;
	int					y_player;
	int					height;
	int					width;
}						t_map;

typedef struct s_data
{
	void				*img;
	unsigned int		*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_data;

typedef struct s_texture_data
{
	t_data				data;
	int					width;
	int					height;
}						t_texture_data;

typedef struct s_rgb
{
	int					red;
	int					green;
	int					blue;
}						t_rgb;

typedef struct s_texture
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*f_tex;
	char				*c_tex;
	t_rgb				*f_rgb;
	t_rgb				*c_rgb;
}						t_texture;

typedef struct s_vars
{
	void				*mlx;
	void				*win;
	double				x_pos;
	double				y_pos;
	double				x_dir;
	double				y_dir;
	double				x_cam_plane;
	double				y_cam_plane;
	unsigned int		floor_col;
	unsigned int		ceil_col;
}						t_vars;

typedef struct s_flag
{
	int					map;
}						t_flag;

typedef struct s_ray
{
	double				x_dir;
	double				y_dir;
	int					x_map;
	int					y_map;
	double				x_side_dist;
	double				y_side_dist;
	double				x_delta_dist;
	double				y_delta_dist;
}						t_ray;

struct					s_info
{
	t_map				map;
	t_vars				vars;
	t_flag				flag;
	t_data				data;
	t_texture			texture;
	t_texture_data		texture_list[TEXTURE_LIST_SIZE];
};

typedef struct s_draw_wall
{
	int					side;
	double				wall_dist;
	int					line_height;
	int					start_y;
	int					end_y;
}						t_draw_wall;

typedef struct s_draw_texture
{
	int					index;
	double				wall_x;
	int					x_coord;
	double				span;
	double				current_pos;
}						t_draw_texture;

typedef struct s_draw_background
{
	float				x_span;
	float				y_span;
	float				x_coord;
	float				y_coord;
}						t_draw_background;

// init
void					init(t_info *info);

// ------------------------------------------------
// FILE
// ------------------------------------------------

// MAP

void					read_file(char *path, t_info *info);
void					get_data_file(int fd, t_info *info);
void					check_map_wall(t_info *info);
void					check_only_one_nswe(t_map *map);
int						mapdata_width_length(char *width);
int						maxwidth_length(t_map *map);
void					updata_pos_map(t_vars *vars, t_info *info, int keycode);
char					**map_str_add(char **array, char *new);

// FILE
int						check_num(char *num_str);
void					init_rgb_values(t_rgb *rgb);
int						check_num(char *num_str);
int						check_texture_section(char *str);
void					handle_texture_part(int fd, char **str, t_info *info,
							int *count);
int						read_texture(char *str, t_texture *texture);
char					*assign_to_structure(char **str, char *identifier,
							t_texture *texture);
void					parse_and_assign_rgb_values(char *path,
							char *identifier, t_texture *texture);
int						first_word_len(char **str);
int						mapdata_width_length(char *width);
int						skip_new_line(char **map_data);
int						skip_space_width(char **map_data, int _y);

// ------------------------------------------------
// MINIMAP
// ------------------------------------------------

int						minimap(t_info *info, t_data *data);
void					central_draw_one_block(t_info *info, int draw_x,
							int draw_y, int color);
void					draw_ray_player_fov(t_info *info, int start_x,
							int start_y);
void					central_map(t_info *info);
void					corner_map(t_info *info, t_data *data);
void					corner_draw_one_block(t_info *info, int draw_x,
							int draw_y, int color);

// ------------------------------------------------
// PLAYER
// ------------------------------------------------

int						key_hook(int keycode, t_vars *vars);
int						ft_key_hook(int keycode, t_info *info);
int						player_coordinate(t_info *info);
void					init_player_coordinate(t_map *map, t_info *info);
void					player_move(t_info *info, int keycode);

// ------------------------------------------------
// RAYCASTING
// ------------------------------------------------

void					raycasting(t_info *info);
void					clean_image(t_data *data);
void					create_xpm_textures(t_texture *texture, t_info *info);
void					destruct_raycasting(t_info *info);
void					draw_color_floor_and_ceil(t_data *data,
							unsigned int floor_col, unsigned int ceil_col);
int						draw_wall(t_info *info);
void					*exit_mlx_new_image(void *mlx);
void					*exit_mlx_new_window(void *mlx);
void					*exit_mlx_init(void);
int						get_nearest_axis(t_ray *ray, t_info *info);
void					init_nswe_dirction(char player_dir, t_vars *vars);
int						key_action(int keycode, t_info *info);
void					my_mlx_pixel_put_line(t_data *data, int x_axis,
							int y_axis[2], unsigned int color);
int						mouse_action(int mousecode, t_info *info);
void					put_texture_ceil(t_draw_background *draw, t_info *info,
							int coord_screen[2], int cell[2]);
void					put_texture_floor(t_draw_background *draw, t_info *info,
							int coord_screen[2], int cell[2]);
void					set_draw_texture_data(t_draw_texture *texture,
							t_draw_wall *wall, t_ray *ray, t_info *info);
void					set_draw_wall_data(t_draw_wall *wall, t_ray *ray,
							t_info *info);
void					try_draw_texture_floor_and_ceil(t_info *info);

// ------------------------------------------------
// WINDOW
// ------------------------------------------------

void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
int						close_window(t_info *info);
int						new_window(t_vars *vars);

// ------------------------------------------------
// ERROR
// ------------------------------------------------

// free
void					free_mapdata(char **map_data, int vertical);
void					free_texture(t_info *info);

// print_error
void					print_error(char *str);

// ------------------------------------------------
// DEBUG
// ------------------------------------------------

void					debug_print_mapdata(t_info *info);

#endif
