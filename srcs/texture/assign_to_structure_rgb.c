/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_to_structure_rgb.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:16:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/01 15:17:53 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// 空白が続くまで単語を読み取る
int	double_pointer_word_len(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] != ' ' && ((*str)[i] != '\t') && ((*str)[i] != '\0')
		&& ((*str)[i] != '\n'))
		i++;
	return (i);
}


// RGB値を設定する関数
static void set_rgb_values(t_rgb *rgb_struct, int rgb, int index)
{
    if (index == 0)
        rgb_struct->red = rgb;
    else if (index == 1)
        rgb_struct->green = rgb;
    else if (index == 2)
        rgb_struct->blue = rgb;
}

// RGB値を取得し、適切な場所に設定する関数
static void assign_rgb_value(char *num_str, t_texture *texture, char *identifier, int index)
{
    int rgb = ft_atoi(num_str);
    free(num_str);

    // カラーコードの範囲を超えていないかチェック
    if (rgb < 0 || 255 < rgb)
    {
        print_error("rgb");
    }

    if (ft_strncmp(identifier, "floor", 6) == 0)
        set_rgb_values(texture->f_rgb, rgb, index);
    else if (ft_strncmp(identifier, "celling", 8) == 0)
        set_rgb_values(texture->c_rgb, rgb, index);
}

// RGB値を分解し、各要素に対して値を設定する関数
void parse_and_assign_rgb_values(char *path, char *identifier, t_texture *texture)
{
    char *num;
    int rgb_index = 0;
    int i = 0;

    while (1)
    {
        num = (char *)malloc(sizeof(char) * (double_pointer_word_len(&path) + 1));
        int j = 0;

        while (path[i] != ',' && path[i] != '\0')
        {
            num[j++] = path[i++];
        }
        num[j] = '\0';

        assign_rgb_value(num, texture, identifier, rgb_index);

        if (path[i] == '\0')
            break ;

        i++;
        rgb_index++;
    }
}
