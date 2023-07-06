/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:26:35 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 19:35:35 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	central_draw_one_block(t_info *info, int draw_x, int draw_y, int color)
{
	int	x;
	int	y;

	x = draw_x;
	while (x < draw_x + BLOCK_SIZE)
	{
		y = draw_y;
		while (y < (draw_y + BLOCK_SIZE))
		{
			my_mlx_pixel_put(info->data, x, y, color);
			y++;
		}
		x++;
	}
}

void	corner_draw_one_block(t_info *info, int draw_x, int draw_y, int color)
{
	int	x;
	int	y;

	x = (draw_x * BLOCK_SIZE);
	while (x < ((draw_x * BLOCK_SIZE) + BLOCK_SIZE))
	{
		y = (draw_y * BLOCK_SIZE);
		while (y < ((draw_y * BLOCK_SIZE) + BLOCK_SIZE))
		{
			my_mlx_pixel_put(info->data, x, y, color);
			y++;
		}
		x++;
	}
}
