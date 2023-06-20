#ifndef CUB3D_H
# define CUB3D_H

# include "../srcs/get_next_line/get_next_line.h"
# include "../srcs/libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>


//------------------------------
//			WINDOW
//------------------------------
# define WIN_WIDTH 1000
# define WIN_HEIGHT 500

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

//キーを押した時の移動距離
# define MOVE_DISTANCE 0.5
# define ABS(a) ((a) < 0 ? -(a) : (a))
# define FOV 40

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

typedef struct s_map
{
	char	**map_data;
	int		height;
	int		width;
}			t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	// double	camera_x;
	// double	camera_y;
}			t_player;

typedef struct s_plane
{
	double 	x;
	double 	y;
}			t_plane;


typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	// key_action
	double	x_position_vector; // posX
	double	y_position_vector; // posY
	double	x_direction; // dirX
	double	y_direction; // dirY
	double	x_camera_plane; // planeX
	double	y_camera_plane; // planeY
	int		screen_width; // width of the screen
	int		screen_height; // height of the screen
	t_data	*image;
}			t_vars;

typedef struct s_flag
{
	int		map;
}				t_flag;

typedef struct s_info
{
	t_map		*map;
	t_vars		*vars;
	t_player	*player;
	t_data		*data;
	t_plane		*plane;
	t_flag		*flag;
}			t_info;

typedef struct s_ray {
	//rayベクトルのx,y成分
	double	x_direction;
	double	y_direction;
	//rayのマップ上の現在のブロックのx,y座標
	int		current_x_in_map;
	int		current_y_in_map;
	//rayが壁にぶつかるまでのx,y距離
	double	x_side_distance;
	double	y_side_distance;
	//rayが次のx,y方向のブロックの境界に到達するたびに
	//side_distanceに加えるべき距離を表します。
	double	x_delta_distance;
	double	y_delta_distance;
} 				t_ray;

//init
void		init(t_info *info, t_map *map, t_player *player, t_vars *vars);
void		init_map(t_map *map);

// ------------------------------------------------
// MAP
// ------------------------------------------------

void		read_map(char *path, t_info *info);
void		get_map_data(int fd, t_info *info);
void		check_map_wall(t_info *info);
void		check_only_one_nswe(t_map *map);
int			minimap(t_info *info, t_data *data);
void 		central_map(t_info *info);
void		range_to_display_with_player(t_info *info, t_data *data);
void		draw_one_block(t_data *data, int draw_x, int draw_y, int color);
int			mapdata_width_length(char *width);
int			mapdata_maxwidth_length(t_map *map);

// ------------------------------------------------
// ERROR
// ------------------------------------------------

//free
void		free_mapdata(char **map_data, int vertical);
//print_error
void		print_error(char *str);

// ------------------------------------------------
// PLAYER
// ------------------------------------------------

int			key_hook(int keycode, t_vars *vars);
int			ft_key_hook(int keycode, t_info *info);
int			player_coordinate(t_info *info);
void		init_player_coordinate(t_player *player, t_map *map);
void		player_move(t_info *info, int keycode);

// ------------------------------------------------
// RAYCASTING
// ------------------------------------------------

int	raycasting(t_info *info);


// ------------------------------------------------
// WINDOW
// ------------------------------------------------

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			close_window(t_vars *vars);
int			new_window(t_vars *vars);

// ------------------------------------------------
// DEBUG
// ------------------------------------------------

void		debug_print_mapdata(t_info *info);

#endif