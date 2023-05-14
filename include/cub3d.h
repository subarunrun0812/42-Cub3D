#ifndef CUB3D_H
#define CUB3D_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mlx.h>
#include "../srcs/get_next_line/get_next_line.h"
#include "../srcs/libft/libft.h"

#define TRUE 0
#define FALSE 1

#define WIN_WIDTH 960
#define WIN_HEIGHT 540

#define WHITE 0x00FFFFFF
#define BLACK 0x00000000
#define GREEN 0x00008000
#define RED 0x00FF0000
#define BLUE 0x000000FF
#define WHEAT 0x00F5DEB3

#define BLOCK_SIZE 20
#define DISPLAY_RADIUS 70

# define W_KEY 13  
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ON_DESTROY 17
# define ESC_KEY 53

typedef struct s_map
{
    char **map_data;
    int    height;
}              t_map;

typedef struct s_pos
{
    int     x;
    int     y;
} t_pos;

typedef struct s_vars
{
    void    *mlx;
    void    *win;
}               t_vars;


typedef struct s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_info
{
    t_map       *map;
    t_vars      *vars;
    t_pos       *pos;
}               t_info;

//init
void init(t_info *info,t_map *map, t_pos *pos, t_vars *vars);
void init_map(t_map *map);


// ------------------------------------------------
// MAP
// ------------------------------------------------
void            read_map(char *path,t_info *info);
void            get_map_data(int fd,t_info *info);
void            check_map_wall(t_info *info);
void            check_only_one_nswe(t_map *map);
int              minimap(t_info *info);

// ------------------------------------------------
// ERROR
// ------------------------------------------------

//free
void	        free_mapdata(char **map_data, int vertical);
//print_error
void             print_error(char *str);


// ------------------------------------------------
// PLAYER
// ------------------------------------------------
int             key_hook(int keycode, t_vars *vars);
int             ft_key_hook(int keycode, t_vars *vars);
int             player_coordinate(t_info *info);


// ------------------------------------------------
// WINDOW
// ------------------------------------------------
void        	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int             close_window(t_vars *vars);
int             new_window(t_vars *vars);






#endif