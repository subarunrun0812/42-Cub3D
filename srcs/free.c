/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:42:45 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/01 13:35:21 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_texture(t_info *info)
{
	free(info->texture->no);
	free(info->texture->so);
	free(info->texture->we);
	free(info->texture->ea);
	
	if (info->texture->f_tex != NULL)
        free(info->texture->f_tex);
    if (info->texture->c_tex != NULL)
        free(info->texture->c_tex);
}

void	free_mapdata(char **map_data, int vertical)
{
	int i;

	i = 0;
	if (vertical < 1)
		return ;
	while (i < vertical)
	{
		free(map_data[i]);
		i++;
	}
	free(map_data);
}