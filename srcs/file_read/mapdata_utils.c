/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapdata_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:29:06 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 17:30:25 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//指定した行の文字数(横の長さ)を返す。
int	mapdata_width_length(char *width)
{
	int	i;

	i = 0;
	while (width[i] != '\0')
	{
		i++;
	}
	i -= 2;
	return (i);
}

//文字が一番長い列を求める
int	mapdata_maxwidth_length(t_map *map)
{
	int	_y;
	int	_x;
	int	res;

	_y = 0;
	_x = 0;
	res = 0;
	while (map->map_data[_y])
	{
		_x = mapdata_width_length(map->map_data[_y]);
		if (res < _x)
			res = _x;
		_y++;
	}
	return (res);
}

int	skip_new_line(char **map_data)
{
	int	_y;

	_y = 0;
	while (map_data[_y][0] == '\n')
	{
		_y++;
	}
	return (_y);
}

int	skip_space_width(char **map_data, int _y)
{
	int	_x;

	_x = 0;
	while (map_data[_y][_x] == ' ')
	{
		_x++;
	}
	return (_x);
}
