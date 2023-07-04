/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:52:13 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/04 13:30:53 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_raydata *raydata, int x, int y, int color)
{
	unsigned int	*dst;

	dst = raydata->addr + (y * WIN_WIDTH + x);
	*dst = color;
}
