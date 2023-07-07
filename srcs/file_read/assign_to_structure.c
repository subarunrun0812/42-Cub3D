/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_to_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:06:11 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 10:38:10 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	process_texture_path(char *path, char *identifier, t_texture *texture)
{
	xpm_filename_check(path);
	//TOD:一番始めにに初期化したら良さそう
	if (ft_strncmp(identifier, "floor", 6) == 0)
		init_rgb_values(texture->f_rgb);
	else if (ft_strncmp(identifier, "celling", 8) == 0)
		init_rgb_values(texture->c_rgb);
	if (open(path, O_RDONLY) == -1)
	{
		perror("open() texture path");
		print_error("open");
	}
}

char	*process_rgb_values(char *path, char *identifier, t_texture *texture)
{
	parse_and_assign_rgb_values(path, identifier, texture);
	free(path);
	return (NULL);
}

// 壁のtexture、床天井の色をファイルから読み取り
char	*assign_to_structure(char **str, char *identifier, t_texture *texture)
{
	char	*path;
	int		i;

	i = 0;
	while (**str == ' ' || **str == '\t')
		(*str)++;
	path = (char *)malloc(sizeof(char) * (first_word_len(str) + 1));
	while (**str != ' ' && **str != '\t' && **str != '\0' && **str != '\n')
	{
		path[i] = **str;
		if (**str != '\n')
			i++;
		(*str)++;
	}
	path[i] = '\0';
	if (('0' <= *path && *path <= '9') || ((ft_strncmp(identifier, "floor",
					6) == 0) && *path == '\0') || ((ft_strncmp(identifier,
					"celling", 8) == 0) && *path == '\0'))
		return (process_rgb_values(path, identifier, texture));
	else
		process_texture_path(path, identifier, texture);
	return (path);
}
