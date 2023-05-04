/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:42:45 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/28 18:44:19 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

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