/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture_ceil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 13:39:21 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_texture_ceil(t_draw_background *draw, t_info *info,
		int coord_screen[2], int cell[2])
{
	int				coord_texture[2];
	unsigned int	color;

	coord_texture[X_AXIS] = (int)(info->vars.texture_list[CEILING].width
			* (draw->x_coord
				- cell[X_AXIS])) & (info->vars.texture_list[CEILING].width - 1);
	coord_texture[Y_AXIS] = (int)(info->vars.texture_list[CEILING].height
			* (draw->y_coord
				- cell[Y_AXIS])) & (info->vars.texture_list[CEILING].height - 1);
	color = *(info->vars.texture_list[CEILING].data.addr
			+ info->vars.texture_list[CEILING].height * coord_texture[Y_AXIS]
			+ coord_texture[X_AXIS]);
	color = (color >> 1) & 8355711;
	info->data.addr[(WIN_WIDTH * (WIN_HEIGHT
				- coord_screen[Y_AXIS]))
		+ coord_screen[X_AXIS]] = color;
}
