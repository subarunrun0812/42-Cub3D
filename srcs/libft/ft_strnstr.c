/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:07:23 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/15 14:16:25 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *c, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (c[i] == '\0')
		return ((char *)(str));
	if (len == 0)
		return (NULL);
	while (str[i] && i < len)
	{
		j = 0;
		while ((str[i + j] && c[j] == str[i + j]) && i + j < len)
		{
			if (c[j + 1] == 0)
				return ((char *)(str + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char a[] = "aiueo";

// 	printf("%s : %s\n", strnstr(a, "", 0), ft_strnstr(a, "", 0));
// 	printf("%s : %s\n", strnstr(a, "a", 6), ft_strnstr(a, "a", 6));
// 	printf("%s : %s\n", strnstr(a, "i", 6), ft_strnstr(a, "i", 6));
// 	printf("%s : %s\n", strnstr(a, "eui", 6), ft_strnstr(a, "eui", 6));
// 	printf("%s : %s\n", strnstr(a, "ie", 6), ft_strnstr(a, "ie", 6));
// 	printf("%s : %s\n", strnstr(a, "uo", 8), ft_strnstr(a, "uo", 8));
// 	return (0);
// 	/*実行結果
// 	aiueo : aiueo
// 	aiueo : aiueo
// 	iueo : iueo	
// 	(null) : (null)
// 	(null) : (null)
// 	(null) : (null)
// */
// }