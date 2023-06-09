/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:01:49 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/12 15:54:41 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	non_specific_chara(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'N' && str[i] != 'S'
			&& str[i] != 'E' && str[i] != 'W' && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	lack_of_texture(t_info *info)
{
	free_texture(info);
	print_error("texture num");
}

void	process_map_data(char **str, t_info *info, int *flag, int fd)
{
	if (non_specific_chara(*str) == 1)
		*flag = 1;
	info->map.map_data = map_str_add(info->map.map_data, *str);
	*str = get_next_line(fd);
	info->map.height++;
	if (*flag == 1)
	{
		free_mapdata(info->map.map_data, info->map.height);
		print_error("get_next_line");
	}
}

void	get_data_file(int fd, t_info *info)
{
	char	*str;
	int		flag;
	int		count;

	str = get_next_line(fd);
	if (!str)
		print_error("get_next_line");
	flag = 0;
	count = 0;
	while (str)
	{
		if (ft_strstr(str, "NO") == NULL && ft_strstr(str, "SO") == NULL
			&& ft_strstr(str, "WE") == NULL && ft_strstr(str, "EA") == NULL
			&& ft_strstr(str, "F") == NULL && ft_strstr(str, "C") == NULL)
			process_map_data(&str, info, &flag, fd);
		else if (check_texture_section(str) == 0)
		{
			count += read_texture(str, &info->texture);
			free(str);
			str = get_next_line(fd);
		}
		if (count < 6 && str == NULL)
			lack_of_texture(info);
	}
}
