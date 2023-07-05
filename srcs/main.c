/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:58:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/05 13:58:47 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	debug_print_mapdata(t_info *info)
{
	for (int i = 0; i < info->map->height; i++)
	{
		for (int j = 0; j< mapdata_width_length(info->map->map_data[i]) + 1; j++)
		{
			if (info->map->map_data[i][j] == 'N')
				printf("\x1b[32m%c\x1b[0m", info->map->map_data[i][j]);
			else
				printf("%c", info->map->map_data[i][j]);
		}
		printf("\n");
	}
	
	return ;
}


int	main(int argc, char **argv)
{
	t_info info;
	t_map map;
	t_vars vars;
	t_data data;
	t_flag flag;
	t_texture texture;
	t_rgb   f_rgb;
    t_rgb   c_rgb;

	if (argc != 2)
		print_error("no map specified.");
	init(&info, &map, &vars, &data);
	init_second(&info, &flag, &texture);
	info.texture->f_rgb = &f_rgb; 
	info.texture->c_rgb = &c_rgb; 
	read_file(argv[1], &info);
	init_player_coordinate(&map,&info);
	raycasting(&info);
	free_texture(&info);
	// exit(0);
	return (0);
}


#define DEBUG_LEAKS_CMD_LEN (32)

__attribute__((destructor))
static void    destructor(void) {
    char    cmd[DEBUG_LEAKS_CMD_LEN];

    snprintf(cmd, DEBUG_LEAKS_CMD_LEN, "leaks %d", getpid());
    system(cmd);
}
