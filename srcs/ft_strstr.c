/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:55:45 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/10 13:58:43 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_strstr(const char *str, const char *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (c[i] == '\0')
		return ((char *)(str));
	while (str[i])
	{
		j = 0;
		while ((str[i + j] && c[j] == str[i + j]))
		{
			if (c[j + 1] == 0)
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
