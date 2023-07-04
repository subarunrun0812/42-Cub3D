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

//------------------------------
//			RAYCASTING
//------------------------------

# define X_AXIS true
# define Y_AXIS false

# define X 0
# define Y 1

//キーを押した時の移動距離
# define MOVE_DISTANCE 0.5
// aの絶対値を返す
# define ABS(a) ((a) < 0 ? -(a) : (a))

//------------------------------
//			TEXTURE
//------------------------------

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define TEXTURE_LIST_SIZE 10
#define FLOOR_1 0
#define FLOOR_2 1
#define CEILING 2
#define SOUTH_WALL 3
#define NORTH_WALL 4
#define EAST_WALL 5
#define WEST_WALL 6
// # define TEXTURE_PATH_BLUE_STONE "./srcs/raycasting/xpm/bluestone.xpm"
// # define TEXTURE_PATH_COLOR_STONE "./srcs/raycasting/xpm/colorstone.xpm"
// # define TEXTURE_PATH_EAGLE "./srcs/raycasting/xpm/eagle.xpm"
// # define TEXTURE_PATH_GREY_STONE "./srcs/raycasting/xpm/greystone.xpm"
// # define TEXTURE_PATH_MOSSY "./srcs/raycasting/xpm/mossy.xpm"
// # define TEXTURE_PATH_PURPLE_STONE "./srcs/raycasting/xpm/purplestone.xpm"
// # define TEXTURE_PATH_RED_BRICK "./srcs/raycasting/xpm/redbrick.xpm"
// # define TEXTURE_PATH_WOOD "./srcs/raycasting/xpm/wood.xpm"
// # define TEXTURE_PATH_BARREL "./srcs/raycasting/xpm/barrel.xpm"
// # define TEXTURE_PATH_PILLAR "./srcs/raycasting/xpm/pillar.xpm"

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
# define NORTH 'N' //北
# define SOUTH 'S' //南
# define EAST 'E'  //東
# define WEST 'W'  //西

typedef struct s_map
{
	// map_data[y][x]
	char			**map_data;
	int				player_x;
	int				player_y;
	int				height;
	int				width;
}					t_map;

typedef struct s_plane
{
	double			x;
	double			y;
}					t_plane;

typedef struct s_data
{
	void			*img;
	unsigned int	*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_data;

typedef struct	s_texture_data {
	t_data	data;
	int		width;
	int		height;
}	t_texture_data;

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
}					t_rgb;

typedef struct s_texture
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*f_tex;
	char			*c_tex;
	t_rgb			*f_rgb;
	t_rgb			*c_rgb;
}					t_texture;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	double			x_position_vector;
	double 			y_position_vector;
	double 			x_direction;
	double 			y_direction;
	//カメラ平面のx,y成分(FOV)。-1から1の範囲
	double			x_camera_plane;
	double 			y_camera_plane;
	int				screen_width;
	int 			screen_height;
  t_data		*data;
	t_texture_data	texture_list[TEXTURE_LIST_SIZE];
}				t_vars;

typedef struct s_flag
{
	int				map;
}					t_flag;

typedef struct s_ray
{
	// rayベクトルのx,y成分
	double			x_direction;
	double			y_direction;
	// rayのマップ上の現在のブロックのx,y座標
	int				current_x_in_map;
	int				current_y_in_map;
	// rayが壁にぶつかるまでのx,y距離
	double			x_side_distance;
	double			y_side_distance;
	// rayが次のx,y方向のブロックの境界に到達するたびに
	// side_distanceに加えるべき距離を表します。
	double			x_delta_distance;
	double			y_delta_distance;
}					t_ray;

typedef struct s_info
{
	t_map			*map;
	t_vars			*vars;
	t_data			*data;
	t_plane			*plane;
	t_flag			*flag;
	t_ray			*ray;
	t_texture		*texture;
}					t_info;

typedef struct s_draw_wall
{
	int		side;
	double	perpendicular_wall_distance;
	int		line_height;
	int		start;
	int		end;
}	t_draw_wall;

typedef struct s_draw_texture
{
	int		list_number;
	double	wall_x;
	int		x_coordinate;
	double	step;
	double	position;
}	t_draw_texture;

typedef struct s_draw_background {
	float	x_move_amount;
	float	y_move_amount;
	float	x_coordinate;
	float	y_coordinate;
}	t_draw_background;

// init
void				init(t_info *info, t_map *map, t_vars *vars, t_data *data);
void				init_second(t_info *info, t_flag *flag, t_texture *texture);

// ------------------------------------------------
// FILE
// ------------------------------------------------

// MAP
void				read_file(char *path, t_info *info);
void				get_data_file(int fd, t_info *info);
void				check_map_wall(t_info *info);
void				check_only_one_nswe(t_map *map);
int					minimap(t_info *info, t_data *data);
void				central_map(t_info *info);
void				range_to_display_with_player(t_info *info, t_data *data);
void				draw_one_block(t_info *info, int draw_x, int draw_y,
						int color);
int					mapdata_width_length(char *width);
int					mapdata_maxwidth_length(t_map *map);
void				updata_pos_map(t_vars *vars, t_info *info, int keycode);

// FILE
int					read_texture(char *str, t_texture *texture);
char				*assign_to_structure(char **str, char *identifier,
						t_texture *texture);
void				parse_and_assign_rgb_values(char *path, char *identifier,
						t_texture *texture);
void				assign_to_structure_floor(char **str, t_texture *texture);
void				assign_to_structure_celling(char **str, t_texture *texture);
void				assign_to_structure_no(char **str, t_texture *texture);
void				assign_to_structure_so(char **str, t_texture *texture);
void				assign_to_structure_we(char **str, t_texture *texture);
void				assign_to_structure_ea(char **str, t_texture *texture);
int					double_pointer_word_len(char **str);

// ------------------------------------------------
// PLAYER
// ------------------------------------------------

int					key_hook(int keycode, t_vars *vars);
int					ft_key_hook(int keycode, t_info *info);
int					player_coordinate(t_info *info);
void				init_player_coordinate(t_map *map, t_info *info);
void				player_move(t_info *info, int keycode);

// ------------------------------------------------
// RAYCASTING
// ------------------------------------------------

void			raycasting(t_info *info);
void				draw_line(t_ray *ray, t_info *info, int x,
						double wall_distance, bool side);
void				my_mlx_pixel_put_line(t_vars *vars, int x, int y1, int y2,
						unsigned int color);
bool				calculate_nearest_axis(t_ray *ray, t_vars *vars,
						t_info *info);

// ------------------------------------------------
// WINDOW
// ------------------------------------------------

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					close_window(t_info *info);
int					new_window(t_vars *vars);

// ------------------------------------------------
// ERROR
// ------------------------------------------------

// free
void				free_mapdata(char **map_data, int vertical);
void				free_texture(t_info *info);

// print_error
void				print_error(char *str);

// ------------------------------------------------
// DEBUG
// ------------------------------------------------

void				debug_print_mapdata(t_info *info);

#endif
