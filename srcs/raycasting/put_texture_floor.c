/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/06 17:27:20 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	decide_texture_floor(int cell[2])
{
	int	checker_board_pattern;

	checker_board_pattern = (int)((cell[X_AXIS] + cell[Y_AXIS]) & 1);
	if (checker_board_pattern == 0)
	{
		return (FLOOR_1);
	}
	return (FLOOR_2);
}

void	put_texture_floor(t_draw_background *draw, t_vars *vars,
		int coord_screen[2], int cell[2])
{
	int				coord_texture[2];
	int				floor_texture;
	unsigned int	color;

	floor_texture = decide_texture_floor(cell);
	coord_texture[X_AXIS] = (int)(vars->texture_list[floor_texture].width
			* (draw->x_coord
				- cell[X_AXIS])) & (vars->texture_list[floor_texture].width
			- 1);
	coord_texture[Y_AXIS] = (int)(vars->texture_list[floor_texture].height
			* (draw->y_coord
				- cell[Y_AXIS])) & (vars->texture_list[floor_texture].height
			- 1);
	color = *(vars->texture_list[floor_texture].data.addr
			+ vars->texture_list[floor_texture].width
			* coord_texture[Y_AXIS] + coord_texture[X_AXIS]);
	color = (color >> 1) & 8355711;
	vars->data->addr[(WIN_WIDTH * coord_screen[Y_AXIS])
		+ coord_screen[X_AXIS]] = color;
}
