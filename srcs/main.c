/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:58:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/15 12:49:49 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../include/cub3d.h"

void debug_print_mapdata(t_info *info)
{
    int i = 0;
    while (i < info->map->height)
    {
        printf("%s",info->map->map_data[i]);
        i++;
    }
    return ;
}


int main(int argc, char **argv)
{
    t_info info;
    t_map   map;
    t_pos   pos;
    t_vars vars;
    t_data data;
    // t_data data;
    
    if (argc != 2)
    {
        printf("\x1b[31mError:\nno map specified.\x1b[0m\n");
        return (0);
    }
    init(&info,&map, &pos, &vars);
    info.data = &data;
    read_map(argv[1], &info);
    init_player_coordinate(&pos,&map);
    new_window(&vars);

    minimap(&info,&data);
    mlx_hook(vars.win, 2, 1L<<0, &ft_key_hook, &info);
	mlx_hook(vars.win, ON_DESTROY, 1L << 2, &close_window, &vars);
    mlx_loop(vars.mlx);
}