/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nswe_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/06 17:01:05 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_north_player_direction(t_vars *vars)
{
	vars->x_dir = -1.0;
	vars->y_dir = 0.0;
	vars->x_cam_plane = 0.0;
	vars->y_cam_plane = 0.66;
}

static void	set_south_player_direction(t_vars *vars)
{
	vars->x_dir = 1.0;
	vars->y_dir = 0.0;
	vars->x_cam_plane = 0.0;
	vars->y_cam_plane = -0.66;
}

static void	set_east_player_direction(t_vars *vars)
{
	vars->x_dir = 0.0;
	vars->y_dir = 1.0;
	vars->x_cam_plane = 0.66;
	vars->y_cam_plane = 0.0;
}

static void	set_west_player_direction(t_vars *vars)
{
	vars->x_dir = 0.0;
	vars->y_dir = -1.0;
	vars->x_cam_plane = -0.66;
	vars->y_cam_plane = 0.0;
}

void	init_nswe_dirction(char player_dir, t_vars *vars)
{
	if (player_dir == NORTH)
	{
		set_north_player_direction(vars);
	}
	else if (player_dir == SOUTH)
	{
		set_south_player_direction(vars);
	}
	else if (player_dir == EAST)
	{
		set_east_player_direction(vars);
	}
	else if (player_dir == WEST)
	{
		set_west_player_direction(vars);
	}
}
