/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:50:28 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/18 15:53:47 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void init_map(t_map *map)
{
    map->map_data = NULL;
    map->height = 0;
    map->width = 0;
}

void init(t_info *info,t_map *map, t_player *player, t_vars *vars)
{
    info->map = map;
    info->player = player;
    info->vars = vars;
    init_map(info->map);
    // init_window_image(info->vars);
}
