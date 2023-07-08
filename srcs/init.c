/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:50:28 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 15:47:51 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init(t_info *info)
{
	info->map.map_data = NULL;
	info->map.height = 0;
	info->map.width = 0;
	info->flag.map = -1;
}
