/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/05 12:50:13 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			print_error("texture identifier");
		while (*str == ' ' || *str == '\t')
			str++;
		res++;
		// printf("res=%d\n",res);
	}
	return (res);
}

