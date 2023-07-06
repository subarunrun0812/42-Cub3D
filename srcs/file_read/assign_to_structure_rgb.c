/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_to_structure_rgb.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:16:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 18:14:40 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// RGB値を設定する関数
static void	set_rgb_values(t_rgb *rgb_struct, int rgb, int index)
{
	if (index == 0)
		rgb_struct->red = rgb;
	else if (index == 1)
		rgb_struct->green = rgb;
	else if (index == 2)
		rgb_struct->blue = rgb;
}

// rgbの引数が数値であるかチェックする
static int	check_num(char *num_str)
{
	int	i;

	i = 0;
	while (num_str[i] != '\0')
	{
		if (('0' <= num_str[i] && num_str[i] <= '9') || (num_str[i] == '-'
				|| num_str[i] != '+'))
			i++;
		else
			return (-1);
	}
	return (0);
}

// RGB値を取得し、適切な場所に設定する関数
static int	assign_rgb_value(char *num_str, t_texture *texture,
		char *identifier, int index)
{
	int	rgb;

	if (*num_str == '\0')
	{
		free(num_str);
		return (-1);
	}
	if (check_num(num_str) == -1)
		rgb = 255;
	else
		rgb = ft_atoi(num_str);
	free(num_str);
	if (rgb < 0 || 255 < rgb)
		rgb = 255;
	if (ft_strncmp(identifier, "floor", 6) == 0)
		set_rgb_values(texture->f_rgb, rgb, index);
	else if (ft_strncmp(identifier, "celling", 8) == 0)
		set_rgb_values(texture->c_rgb, rgb, index);
	return (0);
}

// rgbの引数が足りない場合
void	missing_rgb_argument(int rgb_index, char *identifier,
		t_texture *texture)
{
	if (ft_strncmp(identifier, "floor", 6) == 0)
	{
		if (rgb_index < 1)
			texture->f_rgb->red = 255;
		if (rgb_index < 2)
			texture->f_rgb->green = 255;
		if (rgb_index < 3)
			texture->f_rgb->blue = 255;
	}
	else if (ft_strncmp(identifier, "celling", 8) == 0)
	{
		if (rgb_index < 1)
			texture->c_rgb->red = 255;
		if (rgb_index < 2)
			texture->c_rgb->green = 255;
		if (rgb_index < 3)
			texture->c_rgb->blue = 255;
	}
}

// RGB値を分解し、各要素に対して値を設定する関数
void	parse_and_assign_rgb_values(char *path, char *identifier,
		t_texture *texture)
{
	char	*num_str;
	int		rgb_index;
	int		i;
	int		j;

	rgb_index = 0;
	i = 0;
	while (1)
	{
		num_str = (char *)malloc(sizeof(char) * (first_word_len(&path) + 1));
		j = 0;
		while (path[i] != ',' && path[i] != '\0')
			num_str[j++] = path[i++];
		num_str[j] = '\0';
		if (assign_rgb_value(num_str, texture, identifier, rgb_index) == 0)
			rgb_index++;
		if (path[i] == '\0')
		{
			if (rgb_index < 3)
				missing_rgb_argument(rgb_index, identifier, texture);
			break ;
		}
		i++;
	}
}
