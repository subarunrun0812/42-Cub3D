/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 13:54:12 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	*g_info;

static unsigned int	create_rgb(int r, int g, int b)
{
	unsigned int	rgb;

	rgb = 0;
	if (r < 0 || 255 < r)
	{
		r = 0;
	}
	if (g < 0 || 255 < g)
	{
		g = 0;
	}
	if (b < 0 || 255 < b)
	{
		b = 0;
	}
	rgb |= (r & 0xFF) << 16;
	rgb |= (g & 0xFF) << 8;
	rgb |= (b & 0xFF);
	return (rgb);
}

static void	initialize_vars(t_info *info)
{
	info->vars.mlx = exit_mlx_init();
	info->vars.win = exit_mlx_new_window(info->vars.mlx);
	info->vars.x_pos = (double)info->map.y_player + 0.500001;
	info->vars.y_pos = (double)info->map.x_player + 0.500001;
	init_nswe_dirction
		(info->map.map_data[info->map.y_player][info->map.x_player],
		&info->vars);
	info->vars.floor_col
		= create_rgb(info->texture.f_rgb->red,
			info->texture.f_rgb->green, info->texture.f_rgb->blue);
	info->vars.ceil_col
		= create_rgb(info->texture.c_rgb->red,
			info->texture.c_rgb->green, info->texture.c_rgb->blue);
	info->data.img = exit_mlx_new_image(info->vars.mlx);
	info->data.addr
		= (unsigned int *)mlx_get_data_addr(info->data.img,
			&info->data.bits_per_pixel,
			&info->data.line_length,
			&info->data.endian);
	clean_image(&info->data);
	create_xpm_textures(&info->texture, info);
	draw_color_floor_and_ceil(&info->data,
		info->vars.floor_col, info->vars.ceil_col);
	try_draw_texture_floor_and_ceil(info);
	draw_wall(info);
}

void	raycasting(t_info *info)
{
	g_info = info;
	initialize_vars(info);
	mlx_put_image_to_window(info->vars.mlx, info->vars.win,
		info->data.img, 0, 0);
	minimap(info, &info->data);
	mlx_key_hook(info->vars.win, key_action, info);
	mlx_mouse_hook(info->vars.win, mouse_action, info);
	mlx_hook(info->vars.win, ON_DESTROY, 1L << ON_DESTROY, close_window, info);
	mlx_loop(info->vars.mlx);
	destruct_raycasting(info);
}
