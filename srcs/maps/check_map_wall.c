/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:24:39 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/22 17:42:34 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

//指定した行の文字数(横の長さ)を返す。
int mapdata_width_length(char *width)
{
    int i;
    i = 0;

    while (width[i] != '\0')
    {
        i++;
    }
	i -= 2;
    return (i);
}
//文字が一番長い行を求める
int	mapdata_maxwidth_length(t_map *map)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = 0;
	res = 0;
	while (map->map_data[i])
	{
		while (map->map_data[i][j] != '\0')
		{
			j++;
		}
		j -= 2;
        if (res < j)
            res = j;
        i++;
	}
    // printf("一番長い行は%d\n",res);
	return (res);
}

//マップの上 or 下が1で囲まれているか確認(0は許容する)
static void	check_map_upper_or_lower(char **map_data,int y)
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

static int skip_new_line(char **map_data)
{
	int _y;
	_y = 0;
	while (map_data[_y][0] == '\n')
	{
		_y++;
	}
	return (_y);
}

static int skip_space_width(char **map_data, int _y)
{
    int _x;
    _x = 0;
    while (map_data[_y][_x] == ' ')
    {
        _x++;
    }
    return (_x);
}

static void check_left_right_handsides(char **map_data,int _y)
{
    int width_len;
    int _x;
    width_len = 0;

    width_len = mapdata_width_length(map_data[_y]);
    _x = skip_space_width(map_data,_y);
    if (map_data[_y][_x] != '1' || map_data[_y][_x] != '1')
        print_error("map is not true. left right handsides");
    return ;
}

//0の周りにスペースがないかチェックする
static void check_space_around_zero(int _y,char **map_data)
{
	int j;
	int tmp_j;
	//壁の次から開始したいため
	j = skip_space_width(map_data,_y) + 1;
	while (map_data[_y][j] != '\0')
	{
		if (map_data[_y][j] == '0' || map_data[_y][j] == 'N'
			|| map_data[_y][j] == 'S' || map_data[_y][j] == 'E' || map_data[_y][j] == 'W')
		{	
			tmp_j = j - 1;
            // printf("\x1b[31mbase = %c,i=%d,tmp_j=%d\x1b[0m\n",map_data[_y][tmp_j],_y,tmp_j);
			while (tmp_j < j + 2)
			{
                // printf("\x1b[32m%c\x1b[0m",map_data[_y-1][tmp_j]);
                // printf("\x1b[32m%c\x1b[0m",map_data[_y][tmp_j]);
                // printf("\x1b[32m%c\x1b[0m",map_data[_y+1][tmp_j]);
                // printf("\n");
				if (map_data[_y-1][j] == ' ' || map_data[_y][tmp_j] == ' '
                || map_data[_y+1][j] == ' ' ||  map_data[_y-1][j] == '\n'
                || map_data[_y][tmp_j] == '\n' || map_data[_y+1][j] == '\n')
				{
					print_error("space around zero");
				}
				tmp_j++;
			}
		}
		j++;
	}
}

void check_map_wall(t_info *info)
{
    int _y;
	int fast;
    _y = skip_new_line(info->map->map_data);
	fast = _y;
    
    while (_y < info->map->height)
    {
        if (_y == fast)
        {
            check_map_upper_or_lower(info->map->map_data,_y);
        }
        else if (_y == info->map->height - 1)
        {
            check_map_upper_or_lower(info->map->map_data,_y);
        }
        else
        {
            //2 ~ 最後-1行目までの処理
            check_left_right_handsides(info->map->map_data,_y);
            check_space_around_zero(_y,info->map->map_data);
        }
        _y++;
    }
}