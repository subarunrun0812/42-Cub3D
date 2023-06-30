/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:30:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/23 13:30:43 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

static int	decide_color(t_ray *ray, bool side,t_info *info)
{
	int	color;

	color = BLACK;
	if (info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '1')
	{
		color = RED;
	}
	else if (info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '2')
	{
		color = GREEN;
	}
	else if (info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '3')
	{
		color = BLUE;
	}
	else if (info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == '4')
	{
		color = WHITE;
	}
	else if (info->map->map_data[ray->current_x_in_map][ray->current_y_in_map] == 'N')
	{
		;
	}
	else
	{
		color = YELLOW;
	}
	//give x and y sides different brightness
	if (side == Y_AXIS)
		color = color / 2;
	return (color);
}

static int	calculate_draw_start(int screen_height, int line_height)
{
	int start;

	start = (-line_height / 2) + (screen_height / 2);
	if(start < 0)
	{
		return (0);
	}
	return (start);
}

static int	calculate_draw_end(int screen_height, int line_height)
{
	int	end;

	end = line_height / 2 + screen_height / 2;
	if (screen_height <= end)
	{
		return (screen_height - 1);
	}
	return (end);
}

void	draw_line(t_ray *ray, t_info *info, int x, double wall_distance, bool side)
{
	// Calculate height of line to draw on screen
	int	line_height;
	// calculate lowest and highest pixel to fill in current stripe
	int	draw_start;
	int draw_end;
	int	color;

	line_height = (int)(info->vars->screen_height / wall_distance);
	draw_start = calculate_draw_start(info->vars->screen_height, line_height);
	draw_end = calculate_draw_end(info->vars->screen_height, line_height);
	color = decide_color(ray, side,info);
	my_mlx_pixel_put_line(info->vars->image, x, draw_start, draw_end, color);
}
