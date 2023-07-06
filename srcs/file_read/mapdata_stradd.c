/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapdata_stradd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:46:02 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/06 17:59:33 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
char	**map_str_add(char **array, char *new)
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
