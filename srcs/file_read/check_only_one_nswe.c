/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_only_one_nswe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:04:16 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/24 15:04:17 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

void check_only_one_nswe(t_map *map)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while (i < map->height)
    {
        j = 0;
        while (map->map_data[i][j])
        {
            if (map->map_data[i][j] == 'N' || map->map_data[i][j] == 'S'
            || map->map_data[i][j] == 'W' || map->map_data[i][j] == 'E')
                count++;
            j++;
        }
        i++;
    }
    if (count > 1 || count == 0)
    {
        print_error("Incorrect number of NSWE");
        exit (1);
    }
    return ;
}
