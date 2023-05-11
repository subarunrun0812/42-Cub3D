/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:50:28 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/11 17:30:11 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

void init_map(t_map *map)
{
    map->map_data = NULL;
    map->height = 0;
}

void init(t_info *info)
{
    info->map = malloc(sizeof(t_map));
    info->pos = malloc(sizeof(t_pos));
    init_map(info->map);
    // init_window_image(info->vars);
}
