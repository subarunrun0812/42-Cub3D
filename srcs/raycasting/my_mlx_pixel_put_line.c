/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:30:44 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/04 13:01:50 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

//与えられた色で指定されたx座標にある範囲内のピクセルライン（y1からy2までの垂直ライン）を描画する。
void	my_mlx_pixel_put_line(t_vars *vars, int x, int y1, int y2,unsigned int color)
{
	// printf("my_mlx_pixel_put_line\n");
	int				y;
	unsigned int	*dst;

	y = y1;
	while (y <= y2)
	{
		dst = vars->raydata->addr + (y * WIN_WIDTH + x);
		*dst = color;
		y += 1;
	}
}