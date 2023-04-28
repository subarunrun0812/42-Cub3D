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

// read_map
int              read_map(char *path);

//print_error
void             print_error(char *str);




#endif