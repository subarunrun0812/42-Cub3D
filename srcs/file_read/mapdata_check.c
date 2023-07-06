/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapdata_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:24:39 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 18:00:51 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//マップの上 or 下が1で囲まれているか確認(0は許容する)
static void	check_map_upper_or_lower(char **map_data, int y)
{
	int	x;

	x = 0;
	while (map_data[y][x] != '\n')
	{
		if (map_data[y][x] != '1' && map_data[y][x] != ' ')
		{
			print_error("map is not true. upper lower");
		}
		x++;
	}
}

static void	check_left_right_handsides(char **map_data, int _y)
{
	int	width_len;
	int	_x;

	width_len = 0;
	width_len = mapdata_width_length(map_data[_y]);
	_x = skip_space_width(map_data, _y);
	if (map_data[_y][_x] != '1' || map_data[_y][_x] != '1')
		print_error("map is not true. left right handsides");
	return ;
}

static void	check_space_around_zero(int y, char **map_data)
{
	int	j;
	int	tmp_j;

	j = skip_space_width(map_data, y) + 1;
	while (map_data[y][j] != '\0')
	{
		if (map_data[y][j] == '0' || map_data[y][j] == 'N'
			|| map_data[y][j] == 'S' || map_data[y][j] == 'E'
			|| map_data[y][j] == 'W')
		{
			tmp_j = j - 1;
			while (tmp_j < j + 2)
			{
				if (j >= mapdata_width_length(map_data[y - 1])
					|| j >= mapdata_width_length(map_data[y + 1]))
					print_error("hidden space around zero");
				if (map_data[y - 1][j] == ' ' || map_data[y][tmp_j] == ' '
					|| map_data[y + 1][j] == ' ' || map_data[y - 1][j] == '\n'
					|| map_data[y][tmp_j] == '\n' || map_data[y + 1][j] == '\n')
					print_error("space around zero");
				tmp_j++;
			}
		}
		j++;
	}
}

void	check_map_wall(t_info *info)
{
	int	_y;
	int	fast;

	_y = skip_new_line(info->map->map_data);
	fast = _y;
	while (_y < info->map->height)
	{
		if (_y == fast)
			check_map_upper_or_lower(info->map->map_data, _y);
		else if (_y == info->map->height - 1)
			check_map_upper_or_lower(info->map->map_data, _y);
		else
		{
			check_left_right_handsides(info->map->map_data, _y);
			check_space_around_zero(_y, info->map->map_data);
		}
		_y++;
	}
}
