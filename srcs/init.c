/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:50:28 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 11:01:30 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	init_second(t_info *info, t_flag *flag, t_texture *texture)
// {
// 	info->flag = flag;
// 	info->texture = texture;
// 	info->flag->map = -1;
// }

// void	init(t_info *info, t_map *map, t_vars *vars, t_data *data)
void	init(t_info *info)
{
	// info->map = map;
	// info->vars = vars;
	// info->vars->data = data;
	// info->data = data;
	info->map.map_data = NULL;
	info->map.height = 0;
	info->map.width = 0;
	info->flag.map = -1;
}
