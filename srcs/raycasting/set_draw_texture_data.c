/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_draw_texture_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/06 17:51:16 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	decide_draw_texture(t_ray *ray, t_vars *vars, int side)
{
	if (side == Y_AXIS)
	{
		if (ray->y_map < vars->y_pos)
		{
			return (WEST_WALL);
		}
		return (EAST_WALL);
	}
	else if (ray->x_map < vars->x_pos)
	{
		return (NORTH_WALL);
	}
	return (SOUTH_WALL);
}

static double	get_hit_wall_x(t_draw_wall *wall, t_ray *ray, t_vars *vars)
{
	double	wall_x;

	wall_x = 0.0;
	if (wall->side == X_AXIS)
	{
		wall_x = vars->y_pos + wall->wall_dist
			* ray->y_dir;
	}
	else
	{
		wall_x = vars->x_pos + wall->wall_dist
			* ray->x_dir;
	}
	wall_x -= floor((wall_x));
	return (wall_x);
}

static int	get_x_coordinate_texture(t_draw_texture *texture, t_draw_wall *wall,
		t_ray *ray, t_vars *vars)
{
	int	x_coord_texture;

	x_coord_texture = (int)(texture->wall_x
			* (double)vars->texture_list[texture->index].width);
	if (wall->side == 0 && 0 < ray->x_dir)
	{
		x_coord_texture = vars->texture_list[texture->index].width
			- x_coord_texture - 1;
	}
	if (wall->side == 1 && ray->y_dir < 0)
	{
		x_coord_texture = vars->texture_list[texture->index].width
			- x_coord_texture - 1;
	}
	return (x_coord_texture);
}

void	set_draw_texture_data(t_draw_texture *texture, t_draw_wall *wall,
		t_ray *ray, t_vars *vars)
{
	texture->index = decide_draw_texture(ray, vars, wall->side);
	texture->wall_x = get_hit_wall_x(wall, ray, vars);
	texture->x_coord = get_x_coordinate_texture(texture, wall, ray, vars);
	texture->span = (1.0 * vars->texture_list[texture->index].height)
		/ wall->line_height;
	texture->current_pos = (wall->start_y - (WIN_HEIGHT / 2)
			+ (wall->line_height / 2)) * texture->span;
}
