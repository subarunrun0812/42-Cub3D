/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:58:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/30 12:58:16 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	debug_print_mapdata(t_info *info)
{
	for (int i = 0; i < info->map->height; i++)
	{
		for (int j = 0; j < mapdata_width_length(info->map->map_data[i]); j++)
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
	// t_plane plane;
	if (argc != 2)
	{
		printf("\x1b[31mError:\nno map specified.\x1b[0m\n");
		return (0);
	}
	init(&info, &map, &vars);
	info.data = &data;
	info.flag = &flag;
	info.vars->image = &data;
	info.texture = &texture;
	//TODO:はじめに、角マップを表示したら、centralmap42の時に正常に真ん中に配置されない
	flag.map = -1;
	read_map(argv[1], &info);
	init_player_coordinate(&map,&info);
	raycasting(&info);
}


#define DEBUG_LEAKS_CMD_LEN (32)

__attribute__((destructor))
static void    destructor(void) {
    char    cmd[DEBUG_LEAKS_CMD_LEN];

    snprintf(cmd, DEBUG_LEAKS_CMD_LEN, "leaks %d", getpid());
    system(cmd);
}
