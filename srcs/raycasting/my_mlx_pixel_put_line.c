/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:30:44 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/24 15:06:08 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

//与えられた色で指定されたx座標にある範囲内のピクセルライン（y1からy2までの垂直ライン）を描画する。
void	my_mlx_pixel_put_line(t_data *data, int x, int y1, int y2, int color)
{
	int				y;
	unsigned int	add;
	char			*dst;

	y = y1;
	add = (unsigned int)data->bits_per_pixel / 8;
	while (y <= y2)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
		dst += add;
		y += 1;
	}
}