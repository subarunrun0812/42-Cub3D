/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 13:51:53 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_image(t_data *data)
{
	int	x;
	int	y_axis[2];

	x = 0;
	y_axis[0] = 0;
	y_axis[1] = WIN_HEIGHT - 1;
	while (x < WIN_WIDTH)
	{
		my_mlx_pixel_put_line(data, x, y_axis, 0x00000000);
		x += 1;
	}
}
