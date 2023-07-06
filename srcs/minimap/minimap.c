/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:32:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 19:27:38 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	minimap(t_info *info, t_data *data)
{
	data->addr = (unsigned int *)mlx_get_data_addr(&data->img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (info->flag->map == CORNER)
		corner_map(info, data);
	else
		central_map(info);
	mlx_put_image_to_window(info->vars->mlx, info->vars->win, info->data->img,
		0, 0);
	return (0);
}
