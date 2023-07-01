/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_to_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:06:11 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/01 11:38:53 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


// 空白が続くまで単語を読み取る
int	word_len(char **str)
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
    int rgb = atoi(num_str);

    // カラーコードの範囲を超えていないかチェック
    if (rgb < 0 || 255 < rgb)
        print_error("rgb");

    if (ft_strncmp(identifier, "floor", 6) == 0)
        set_rgb_values(texture->f_rgb, rgb, index);
    else if (ft_strncmp(identifier, "celling", 8) == 0)
        set_rgb_values(texture->c_rgb, rgb, index);
}

// RGB値を分解し、各要素に対して値を設定する関数
static void parse_and_assign_rgb_values(char *path, char *identifier, t_texture *texture)
{
    char *num;
    int rgb_index = 0;
    int i = 0;

    while (1)
    {
        num = (char *)malloc(sizeof(char) * (word_len(&path) + 1));
        int j = 0;

        while (path[i] != ',' && path[i] != '\0')
        {
            num[j++] = path[i++];
        }
        num[j] = '\0';

        assign_rgb_value(num, texture, identifier, rgb_index);

        free(num);

        if (path[i] == '\0')
            break ;

        i++;
        rgb_index++;
    }
}


static void	xpm_filename_check(char *filename)
{
	char	*cub;
	int		i;
	int		len;

	len = ft_strlen(filename);
	cub = ".xpm";
	i = ft_strlen(cub);
	while (cub[i--] == filename[len--])
	{
		if (i == 0)
			break ;
	}
	if (cub[i] != filename[len])
		print_error("filename .xpm");
	return ;
}

// 壁のtexture、床天井の色をファイルから読み取り
char *assign_to_structure(char **str, char *identifier, t_texture *texture)
{
    char *path;
    int i = 0;

    while (**str == ' ' || **str == '\t')
        (*str)++;

    path = (char *)malloc(sizeof(char) * (word_len(str) + 1));

    while (**str != ' ' && **str != '\t' && **str != '\0' && **str != '\n')
    {
        path[i] = **str;

        if (**str != '\n')
            i++;

        (*str)++;
    }
    path[i] = '\0';

    //RGBのカラーコードの場合
    if ('0' <= *path && *path <= '9')
    {
        parse_and_assign_rgb_values(path, identifier, texture);
        return (NULL);
    }
    else // テクスチャの.xpmの場合
    {
        xpm_filename_check(path);

        if (open(path, O_RDONLY) == -1)
        {
            perror("open() texture path");
            print_error("open");
        }
    }
    return (path);
}

