/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:42:45 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 11:00:37 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_texture(t_info *info)
{
	free(info->texture.no);
	free(info->texture.so);
	free(info->texture.we);
	free(info->texture.ea);
	if (info->texture.f_tex != NULL)
		free(info->texture.f_tex);
	if (info->texture.c_tex != NULL)
		free(info->texture.c_tex);
}

// printf("\x1b[32m");
// printf("texture->no=%s\n", info->texture.no);
// printf("texture->so=%s\n", info->texture.so);
// printf("texture->we=%s\n", info->texture.we);
// printf("texture->ea=%s\n", info->texture.ea);
// printf("texture->f_tex=%s\n", info->texture.f_tex);
// printf("texture->c_tex=%s\n", info->texture.c_tex);
// printf("texture->floor->red=%d\n", info->texture.f_rgb->red);
// printf("texture->floor->green=%d\n", info->texture.f_rgb->green);
// printf("texture->floor->blue=%d\n", info->texture.f_rgb->blue);
// printf("texture->celling->red=%d\n", info->texture.c_rgb->red);
// printf("texture->celling->green=%d\n", info->texture.c_rgb->green);
// printf("texture->celling->blue=%d\n", info->texture.c_rgb->blue);
// printf("\x1b[0m\n");

void	free_mapdata(char **map_data, int vertical)
{
	int	i;

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
