/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 14:41:16 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_window(t_vars *vars)
{
	if (vars->mlx != NULL && vars->win != NULL)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	}
}

static void	destroy_textures(t_info *info)
{
	int	i;

	i = 0;
	if (info->vars.mlx == NULL)
	{
		return ;
	}
	while (i < TEXTURE_LIST_SIZE)
	{
		if (info->texture_list[i].data.img != NULL)
		{
			mlx_destroy_image(info->vars.mlx, info->texture_list[i].data.img);
		}
		i += 1;
	}
}

void	destruct_raycasting(t_info *info)
{
	destroy_window(&info->vars);
	destroy_textures(info);
	free(info->vars.mlx);
}
