/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_to_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:06:11 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/01 15:17:50 by susasaki         ###   ########.fr       */
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

// 壁のtexture、床天井の色をファイルから読み取り
char *assign_to_structure(char **str, char *identifier, t_texture *texture)
{
    char *path;
    int i = 0;

    while (**str == ' ' || **str == '\t')
        (*str)++;

    path = (char *)malloc(sizeof(char) * (double_pointer_word_len(str) + 1));

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
        printf("path = %s\n",path);
        free(path);
        path = NULL; // ポインタをNULLに設定
        printf("path = %s\n",path);
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

