/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/30 17:31:31 by susasaki         ###   ########.fr       */
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

char *assign_to_structure(char **str)
{
	char	*path;
	int		i;

	i = 0;
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
    // printf("path=%s\n",path);
	if (*path < '0' || '9' < *path)
	{
		if (open(path, O_RDONLY) == -1)
		{
			perror("open() texture path");
            print_error("open");
		}
	}
    return (path);
}

int	read_texture(char *str, t_texture *texture)
{
	int j;
	int res;
	// char identifier[3];
	j = 0;
	res = 0;

	while (*str != '\n' && *str != '\0')
	{
		char identifier[3];
		j = 0;
		while (*str == ' ' || *str == '\t')
			str++;
		// printf("*str = %c\n", *str);
		// 東西南北、床、天井の識別子を代入
		identifier[j++] = *(str++);
		if (*str != ' ' && *str != '\t')
			identifier[j++] = *(str++);
		identifier[j] = '\0';

        if (ft_strncmp(identifier, "NO", 3) == 0)
		    assign_to_structure_no(&str, texture);
        else if (ft_strncmp(identifier, "SO", 3) == 0)
		    assign_to_structure_so(&str, texture);
        else if (ft_strncmp(identifier, "WE", 3) == 0)
		    assign_to_structure_we(&str, texture);
        else if (ft_strncmp(identifier, "EA", 3) == 0)
		    assign_to_structure_ea(&str, texture);
        else if (ft_strncmp(identifier, "F", 2) == 0)
		    assign_to_structure_floor(&str, texture);
        else if (ft_strncmp(identifier, "C", 2) == 0)
		    assign_to_structure_celling(&str, texture);
        else
			print_error("texture");
		while (*str == ' ' || *str == '\t')
			str++;
		res++;
		// printf("res=%d\n",res);
	}
	return (res);
}