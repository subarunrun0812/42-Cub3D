/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:40:15 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/15 14:39:35 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char test[20] = "123456321";
// 	char *p;
// 	char *q;

// p = ft_strrchr(NULL, '\0');
// q = strrchr(NULL, '\0');

// printf("検索文字が見つかった場所から表示→%s\n", p);
// printf("検索文字が見つかった場所から表示→%s\n", q);

// 	return (0);
// }