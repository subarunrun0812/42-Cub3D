#ifndef CUB3D_H
#define CUB3D_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../srcs/get_next_line/get_next_line.h"
#include "../srcs/libft/libft.h"

#define TRUE 0
#define FALSE 1


typedef struct s_map
{
    char **map_data;
    int    height;
}              t_map;

typedef struct s_info
{
    t_map *map;
}               t_info;

// read_map
void            read_map(char *path,t_info *info);

//get_map_data
void get_map_data(int fd,t_info *info);

//print_error
void             print_error(char *str);

//free
void	free_mapdata(char **map_data, int vertical);

//init
void init(t_info *info);
void init_map(t_map *map);

// check_map_wall.c
void    check_map_wall(t_info *info);

#endif