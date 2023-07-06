/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:45:16 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 17:56:50 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_texture_section(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\0')
		i++;
	if ('0' <= str[i] && str[i] <= '9')
		return (-1);
	return (0);
}

void	handle_texture_part(int fd, char **str, t_info *info, int *count)
{
	if (check_texture_section(*str) == 0)
	{
		*count += read_texture(*str, info->texture);
		free(*str);
		*str = get_next_line(fd);
	}
	else if (*count < 6)
	{
		free_texture(info);
		print_error("texture num");
	}
}
