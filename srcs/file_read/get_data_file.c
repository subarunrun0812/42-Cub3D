/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:01:49 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/05 13:58:49 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	non_specific_chara(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		// TODO: 課題要件にない'2','3','4'を削除する
		if (str[i] != '0' && str[i] != '1' && str[i] != 'N' && str[i] != 'S'
			&& str[i] != 'E' && str[i] != 'W' && str[i] != ' ' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4')
			return (1);
		i++;
	}
	return (0);
}

//新しい行を追加する
static char	*check_n(char *str)
{
	int		i;
	char	*res;

	if (ft_strchr(str, '\n'))
		return (str);
	res = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = '\n';
	res[i] = '\0';
	free(str);
	return (res);
}

// 2次元の文字列配列に新しい行を追加する
static char	**map_str_add(char **array, char *new)
{
	char	**res;
	int		i;
	int		vertical;

	vertical = 0;
	while (array && array[vertical] != NULL)
		vertical++;
	res = (char **)malloc(sizeof(char *) * (vertical + 2));
	if (!res)
		print_error("map");
	i = 0;
	while (i < vertical)
	{
		res[i] = array[i];
		i++;
	}
	new = check_n(new);
	if (!new)
		print_error("check_n()");
	res[i++] = new;
	res[i] = NULL;
	free(array);
	return (res);
}

int check_texture_section(char *str)
{
    int i;
    i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
        i++;
    if ('0' <= str[i] && str[i] <= '9')
        return (-1);
    return (0);
}

void	get_data_file(int fd, t_info *info)
{
	char	*str;
	int		flag;
	int		count;
	int		i;
	str = get_next_line(fd);
	if (!str)
	{
		print_error("get_next_line");
	}
	flag = 0;
	i = 0;
    count = 0;
	while (str)
	{
		if (check_texture_section(str) == 0)
		{
            count += read_texture(str,info->texture);
			free(str);
            str = get_next_line(fd);
			i++;
            // printf("count = %d\n",count);
		}
        else if (count < 6)
		{
			free_texture(info);
            print_error("texture num");
		}
		else
		{
			if (non_specific_chara(str) == 1)
			{
				printf("\x1b[31mstr = %s\x1b[0m\n", str);
				flag = 1;
			}
			info->map->map_data = map_str_add(info->map->map_data, str);
			str = get_next_line(fd);
			i++;
			info->map->height++;
			if (flag == 1)
			{
				free_mapdata(info->map->map_data, info->map->height);
				print_error("get_next_line");
			}
		}
	}
    printf("\x1b[32m");
    printf("texture->no=%s\n",info->texture->no);
    printf("texture->so=%s\n",info->texture->so);
    printf("texture->we=%s\n",info->texture->we);
    printf("texture->ea=%s\n",info->texture->ea);
    printf("texture->f_tex=%s\n",info->texture->f_tex);
    printf("texture->c_tex=%s\n",info->texture->c_tex);
    printf("texture->floor->red=%d\n",info->texture->f_rgb->red);
    printf("texture->floor->green=%d\n",info->texture->f_rgb->green);
    printf("texture->floor->blue=%d\n",info->texture->f_rgb->blue);
    printf("texture->celling->red=%d\n",info->texture->c_rgb->red);
    printf("texture->celling->green=%d\n",info->texture->c_rgb->green);
    printf("texture->celling->blue=%d\n",info->texture->c_rgb->blue);
    printf("\x1b[0m\n");		
}
