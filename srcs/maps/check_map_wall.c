/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:24:39 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/06 17:19:24 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

//指定した行の文字数(横の長さ)を返す。
int mapdata_width_length(char *width)
{
    int i;
    i = 0;

    while (width[i] != '\n')
    {
        i++;
    }
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

    if (width[i] != '1' && width[width_len] != '1')
        print_error("map is not true. left right handsides");
    return ;
}

// void check_space_

void check_map_wall(t_info *info)
{
    printf("map->height=%d\n",info->map->height);
    int i;
    i = 0;
    
    //TODO:2行目の0の斜め上と上の座標が1であるか、左右端が1になっているか確認する
    //TODO:↑同じやり方で最後の行も確認する。
    //TODO:2行目~最後-1行目の上下左右斜めにスペースが無いか確認する
    while (i < info->map->height)
    {
        if (i == 0)
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
            
            
        }
        i++;
    }
}