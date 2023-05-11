/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:34:10 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/11 17:31:00 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

static void	filename_check(char *filename)
{
	char	*cub;
	int		i;
	int		len;

	len = ft_strlen(filename);
	cub = ".cub";
	i = ft_strlen(cub);
	while (cub[i--] == filename[len--])
	{
		if (i == 0)
			break ;
	}
	if (cub[i] != filename[len])
		print_error("filename");
	return ;
}

void	read_map(char *path, t_info *info)
{
	int	fd;

	filename_check(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_error("open");
	get_map_data(fd, info);
	if (info->map->height < 3)
	{
		print_error("map is small\n");
		exit(1);
	}
	// mapが壁で囲まれているかチェックする
	check_map_wall(info);
	check_only_one_nswe(info->map);
	close(fd);
}
