/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/07 11:36:25 by hnoguchi         ###   ########.fr       */
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

static void	destroy_textures(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->mlx == NULL)
	{
		return ;
	}
	while (i < TEXTURE_LIST_SIZE)
	{
		if (vars->texture_list[i].data.img != NULL)
		{
			mlx_destroy_image(vars->mlx, vars->texture_list[i].data.img);
		}
		i += 1;
	}
}

void	destruct_raycasting(t_info *info)
{
	destroy_window(&info->vars);
	destroy_textures(&info->vars);
	free(info->vars.mlx);
}
