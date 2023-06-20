/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:58:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/16 16:44:25 by susasaki         ###   ########.fr       */
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
	t_player player;
	t_vars vars;
	t_data data;
	// t_plane plane;
	if (argc != 2)
	{
		printf("\x1b[31mError:\nno map specified.\x1b[0m\n");
		return (0);
	}
	info.data = &data;
	init(&info, &map, &player, &vars);
	info.vars->image = &data;
	// info.plane = &plane;
	read_map(argv[1], &info);
	init_player_coordinate(&player, &map);
	new_window(&vars);
	raycasting(&info);
	// minimap(&info, &data);
	// mlx_hook(vars.win, 2, 1L << 0, &ft_key_hook, &info);
	// mlx_hook(vars.win, ON_DESTROY, 1L << 2, &close_window, &vars);
	
	mlx_loop(vars.mlx);
}