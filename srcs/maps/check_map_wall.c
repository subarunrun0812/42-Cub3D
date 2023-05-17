/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:24:39 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/17 15:39:29 by susasaki         ###   ########.fr       */
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

//マップの上 or 下が1で囲まれているか確認(0は許容する)
static void	check_map_upper_or_lower(char *width)
{
	int	i;

	i = 0;
	while (width[i] != '\n')
	{
        // printf("width=%s\n",width);
		if (width[i] != '1' && width[i] != ' ')
        {
			print_error("map is not true. upper lower");
            // printf("width[%d]=%c\n",i,width[i]);
        }
		i++;
	}
}

static int skip_new_line(char **map_data)
{
	int i;
	i = 0;
	while (map_data[i][0] == '\n')
	{
		i++;
	}
	return (i);
}

static int skip_space_width(char *width)
{
    int i;
    i = 0;
    while (width[i] == ' ')
    {
        i++;
    }
    return (i);
}

static void check_left_right_handsides(char *width)
{
    int width_len;
    int i;
    width_len = 0;

    width_len = mapdata_width_length(width);
    i = skip_space_width(width);
	// printf("width[%d]=\"%c\"\n",width_len,width[width_len]);
    if (width[i] != '1' || width[width_len] != '1')
        print_error("map is not true. left right handsides");
    return ;
}

//0の周りにスペースがないかチェックする
static void check_space_around_zero(char *width ,int height,char **map_data)
{
	int i;
	int j;
	//壁の次から開始したいため
	i = skip_space_width(width) + 1;
	while (width[i] != '\0')
	{
		if (width[i] == '0' || width[i] == 'N'
			|| width[i] == 'S' || width[i] == 'E' || width[i] == 'W')
		{	
			j = i - 1;
			while (j < 3)
			{
				if (map_data[height-1][j] == ' ' || map_data[height+1][j] == ' ')
				{
					print_error("space around zero");
				}
				j++;
			}
			if (width[i-1] == ' ' || width[i+1] == ' ')
				print_error("space around zero");
		}
		i++;
	}
}

void check_map_wall(t_info *info)
{
    int i;
	int fast;
    i = skip_new_line(info->map->map_data);
	fast = i;
    
    while (i < info->map->height)
    {
        if (i == fast)
        {
            check_map_upper_or_lower(info->map->map_data[i]);
        }
        else if (i == info->map->height - 1)
        {
            check_map_upper_or_lower(info->map->map_data[i]);
        }
        else
        {
            //2 ~ 最後-1行目までの処理
            check_left_right_handsides(info->map->map_data[i]);
            check_space_around_zero(info->map->map_data[i],i,info->map->map_data);
        }
        i++;
    }
}