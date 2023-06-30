/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/30 18:43:55 by susasaki         ###   ########.fr       */
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

char	*assign_to_structure(char **str,char *identifier,t_texture *texture)
{
	char	*path;
	int		i;
	char	*num;
	int		len;
	int		j;
	int		len_i;

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
	// RGBのcheck
	if ('0' <= *path && *path <= '9')
	{
		i = 0;
		len = 0;
		int rgb;
        int _k;
        _k = 0;
		// printf("path=%s\n", path);
		while (1)
		{
			len_i = i;
			while (path[len_i] != ',' && path[len_i] != '\0')
			{
				len_i++;
				len++;
			}
			// printf("len=%d\n", len);
			num = (char *)malloc(sizeof(char) * (len + 1));
			j = 0;
			while (path[i] != ',' && path[i] != '\0')
			{
				num[j] = path[i];
				// printf("path[%d]=%c\n", i, path[i]);
				// printf("nun[%d]=%c\n", j, num[j]);
				i++;
				j++;
			}
			num[j] = '\0';
			rgb = atoi(num);
			// printf("\x1b[32mrgb = %d\x1b[0m\n", rgb);
            if (rgb < 0 || 255 < rgb)
                print_error("rgb");
            if (ft_strncmp(identifier,"floor",6) == 0)
            {
                if (_k == 0)
                    texture->f_rgb->red = rgb;
                if (_k == 1)
                    texture->f_rgb->green = rgb;
                if (_k == 2)
                    texture->f_rgb->blue = rgb;
            }
            if (ft_strncmp(identifier,"celling",8) == 0)
            {
                if (_k == 0)
                    texture->c_rgb->red = rgb;
                if (_k == 1)
                    texture->c_rgb->green = rgb;
                if (_k == 2)
                    texture->c_rgb->blue = rgb;
            }
			free(num);
			if (path[i] == '\0')
				break ;
			i++;
            _k++;
		}
	}
	else
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