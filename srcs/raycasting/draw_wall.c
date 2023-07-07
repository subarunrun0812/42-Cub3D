/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 15:48:07 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_texture(t_draw_texture *texture, t_draw_wall *wall,
		t_info *info, int x_coordinate_screen)
{
	unsigned int	color;
	int				y_coordinate_screen;
	int				y_coordinate_texture;

	y_coordinate_screen = wall->start_y;
	while (y_coordinate_screen < wall->end_y)
	{
		y_coordinate_texture
			= (int)texture->current_pos
			& (info->texture_list[texture->index].height
				- 1);
		texture->current_pos += texture->span;
		color = *(info->texture_list[texture->index].data.addr
				+ info->texture_list[texture->index].height
				* y_coordinate_texture + texture->x_coord);
		if (wall->side == Y_AXIS)
		{
			color = (color >> 1) & 8355711;
		}
		info->data.addr[y_coordinate_screen * WIN_WIDTH
			+ x_coordinate_screen] = color;
		y_coordinate_screen += 1;
	}
}

static void	set_ray_data(t_ray *ray, t_vars *vars, int x)
{
	double	x_current_cam;

	x_current_cam = 2 * x / (double)WIN_WIDTH - 1;
	ray->x_dir = vars->x_dir + (vars->x_cam_plane
			* x_current_cam);
	ray->y_dir = vars->y_dir + (vars->y_cam_plane
			* x_current_cam);
	ray->x_map = (int)vars->x_pos;
	ray->y_map = (int)vars->y_pos;
	ray->x_side_dist = 0;
	ray->y_side_dist = 0;
	if (ray->x_dir == 0)
	{
		ray->x_delta_dist = 1e30;
	}
	else
		ray->x_delta_dist = ABS(1 / ray->x_dir);
	if (ray->y_dir == 0)
	{
		ray->y_delta_dist = 1e30;
	}
	else
		ray->y_delta_dist = ABS(1 / ray->y_dir);
}

int	draw_wall(t_info *info)
{
	int				x_coordinate_screen;
	t_ray			ray;
	t_draw_wall		wall;
	t_draw_texture	texture;

	x_coordinate_screen = 0;
	while (x_coordinate_screen < WIN_WIDTH)
	{
		set_ray_data(&ray, &info->vars, x_coordinate_screen);
		set_draw_wall_data(&wall, &ray, info);
		set_draw_texture_data(&texture, &wall, &ray, info);
		put_texture(&texture, &wall, info, x_coordinate_screen);
		x_coordinate_screen += 1;
	}
	return (0);
}
