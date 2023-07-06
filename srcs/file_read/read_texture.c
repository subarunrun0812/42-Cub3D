/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 17:48:42 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_spaces_skip(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

// テクスチャ識別子を読み込む関数
void	read_texture_identifier(char **str, char *identifier)
{
	int	j;

	j = 0;
	while (**str == ' ' || **str == '\t')
		(*str)++;
	identifier[j++] = *((*str)++);
	if (**str != ' ' && **str != '\t')
		identifier[j++] = *((*str)++);
	identifier[j] = '\0';
}

int	read_texture(char *str, t_texture *texture)
{
	int		res;
	char	identifier[3];

	res = 0;
	while (*str != '\n' && *str != '\0')
	{
		read_texture_identifier(&str, identifier);
		if (ft_strncmp(identifier, "NO", 3) == 0)
			texture->no = assign_to_structure(&str, "no", texture);
		else if (ft_strncmp(identifier, "SO", 3) == 0)
			texture->so = assign_to_structure(&str, "so", texture);
		else if (ft_strncmp(identifier, "WE", 3) == 0)
			texture->we = assign_to_structure(&str, "we", texture);
		else if (ft_strncmp(identifier, "EA", 3) == 0)
			texture->ea = assign_to_structure(&str, "ea", texture);
		else if (ft_strncmp(identifier, "F", 2) == 0)
			texture->f_tex = assign_to_structure(&str, "floor", texture);
		else if (ft_strncmp(identifier, "C", 2) == 0)
			texture->c_tex = assign_to_structure(&str, "celling", texture);
		else
			print_error("texture identifier");
		check_spaces_skip(&str);
		res++;
	}
	return (res);
}
