/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_xpm_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 14:12:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_create_texture(t_info *info,
		char *path, t_texture_data *texture)
{
	texture->data.img
		= mlx_xpm_file_to_image(info->vars.mlx, path,
			&texture->width, &texture->height);
	if (texture->data.img == NULL)
	{
		destruct_raycasting(info);
		print_error("small texture.");
	}
	texture->data.addr
		= (unsigned int *)mlx_get_data_addr(texture->data.img,
			&texture->data.bits_per_pixel,
			&texture->data.line_length,
			&texture->data.endian);
	if (texture->width != 64 || texture->height != 64)
	{
		destruct_raycasting(info);
		print_error("small texture.");
	}
}

static void	create_texture_floor(t_info *info,
		char *path, t_texture_data *texture_list)
{
	if (path == NULL)
	{
		texture_list[FLOOR_1].data.img = NULL;
		texture_list[FLOOR_1].data.addr = NULL;
		texture_list[FLOOR_2].data.img = NULL;
		texture_list[FLOOR_2].data.addr = NULL;
		return ;
	}
	exit_create_texture(info, path, &texture_list[FLOOR_1]);
	exit_create_texture(info,
		"./srcs/raycasting/xpm/bluestone.xpm", &texture_list[FLOOR_2]);
}

static void	create_texture_ceil(t_info *info,
		char *path, t_texture_data *texture)
{
	if (path == NULL)
	{
		texture->data.img = NULL;
		texture->data.addr = NULL;
		return ;
	}
	exit_create_texture(info, path, texture);
}

static void	initialize_texture_list(t_texture_data *texture_list)
{
	int	i;

	i = 0;
	while (i < TEXTURE_LIST_SIZE)
	{
		texture_list[i].data.img = NULL;
		i += 1;
	}
}

void	create_xpm_textures(t_texture *texture, t_info *info)
{
	initialize_texture_list(info->texture_list);
	create_texture_floor(info, texture->f_tex, info->texture_list);
	create_texture_ceil(info,
		texture->c_tex, &info->texture_list[CEILING]);
	exit_create_texture(info,
		texture->so, &info->texture_list[SOUTH_WALL]);
	exit_create_texture(info,
		texture->no, &info->texture_list[NORTH_WALL]);
	exit_create_texture(info,
		texture->ea, &info->texture_list[EAST_WALL]);
	exit_create_texture(info,
		texture->we, &info->texture_list[WEST_WALL]);
}
