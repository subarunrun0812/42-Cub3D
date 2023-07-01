/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:50:28 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/01 11:49:49 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_second(t_info *info, t_flag *flag, t_texture *texture)
{
	info->flag = flag;
	info->texture = texture;
	//TODO:はじめに、角マップを表示したら、centralmap42の時に正常に真ん中に配置されない
	info->flag->map = -1;
}

void	init(t_info *info, t_map *map, t_vars *vars, t_data *data)
{
	info->map = map;
	info->vars = vars;
	info->vars->image = data;
	info->data = data;
	map->map_data = NULL;
	map->height = 0;
	map->width = 0;
}