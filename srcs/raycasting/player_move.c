/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:54:54 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/12 14:09:43 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(char **map, t_vars *vars)
{
	int		one_forward_x_pos_vec;
	int		one_forward_y_pos_vec;
	char	distination;

	one_forward_x_pos_vec = vars->x_pos + (vars->x_dir * MOVE_DIST);
	one_forward_y_pos_vec = vars->y_pos + (vars->y_dir * MOVE_DIST);
	distination = map[one_forward_x_pos_vec][one_forward_y_pos_vec];
	if (distination == '1')
		return ;
	else
	{
		vars->x_pos += vars->x_dir * MOVE_DIST;
		vars->y_pos += vars->y_dir * MOVE_DIST;
	}
}

void	move_backward(char **map, t_vars *vars)
{
	int		one_backward_x_pos_vec;
	int		one_backward_y_pos_vec;
	char	distination;

	one_backward_x_pos_vec = vars->x_pos + (-vars->x_dir * MOVE_DIST);
	one_backward_y_pos_vec = vars->y_pos + (-vars->y_dir * MOVE_DIST);
	distination = map[one_backward_x_pos_vec][one_backward_y_pos_vec];
	if (distination == '1')
		return ;
	else
	{
		vars->x_pos += -vars->x_dir * MOVE_DIST;
		vars->y_pos += -vars->y_dir * MOVE_DIST;
	}
}

void	move_right(char **map, t_vars *vars)
{
	int		one_right_x_pos_vec;
	int		one_right_y_pos_vec;
	char	destination;

	one_right_x_pos_vec = vars->x_pos + (vars->y_dir * MOVE_DIST);
	one_right_y_pos_vec = vars->y_pos + (-vars->x_dir * MOVE_DIST);
	destination = map[one_right_x_pos_vec][one_right_y_pos_vec];
	if (destination == '1')
		return ;
	else
	{
		vars->x_pos += vars->y_dir * MOVE_DIST;
		vars->y_pos += -vars->x_dir * MOVE_DIST;
	}
}

void	move_left(char **map, t_vars *vars)
{
	int		one_left_x_pos_vec;
	int		one_left_y_pos_vec;
	char	destination;

	one_left_x_pos_vec = vars->x_pos + (-vars->y_dir * MOVE_DIST);
	one_left_y_pos_vec = vars->y_pos + (vars->x_dir * MOVE_DIST);
	destination = map[one_left_x_pos_vec][one_left_y_pos_vec];
	if (destination == '1')
		return ;
	else
	{
		vars->x_pos += -vars->y_dir * MOVE_DIST;
		vars->y_pos += vars->x_dir * MOVE_DIST;
	}
}
