/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/30 17:02:01 by susasaki         ###   ########.fr       */
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
	// printf("assign_to_structure_no()\n");
	while (**str == ' ' || **str == '\t')
		(*str)++;
	// printf("str=%s",*str);
	path = (char *)malloc(sizeof(char) * (word_len(str) + 1));
	while (**str != ' ' && **str != '\t' && **str != '\0')
	{
		// path[i++] = (**str)++;
		path[i] = **str;
		// printf("path[%d]=%c\n",i,path[i]);
		// printf("**str=%c\n",**str);
		i++;
		(*str)++;
	}
	i--;
	path[i] = '\0';
	// printf("path=%s\n", path);
	if ('0' > *path && *path > '9')
	{
		if (open(path, O_RDONLY) == -1)
		{
			perror("open() texture path");
			// print_error("done");
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
		// printf("identifier = %s\n", identifier);
		if (*str != ' ' && *str != '\t')
		{
			// printf("str=%s\n", str);
			print_error("texture 識別子が3文字以上");
		}
        if (ft_strncmp(identifier, "NO", 2) == 0)
		    assign_to_structure_no(&str, texture);
        else if (ft_strncmp(identifier, "SO", 2) == 0)
		    assign_to_structure_so(&str, texture);
        else if (ft_strncmp(identifier, "WE", 2) == 0)
		    assign_to_structure_we(&str, texture);
        else if (ft_strncmp(identifier, "EA", 2) == 0)
		    assign_to_structure_ea(&str, texture);
        else if (ft_strncmp(identifier, "F", 1) == 0)
		    assign_to_structure_floor(&str, texture);
        else if (ft_strncmp(identifier, "C", 1) == 0)
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