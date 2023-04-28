/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:19:47 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/15 14:58:53 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*(str1 + i) == 0 && *(str2 + i) == 0)
			return (0);
		if (*(str1 + i) != *(str2 + i))
			return (*(str1 + i) - *(str2 + i));
		i++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	printf("%d\n", ft_strncmp("atoms\0\0\0\0", "atoms\0abc", 8));
// 	printf("%d\n", strncmp("atoms\0\0\0\0", "atoms\0abc", 8));
// 	/*
// 	printf("%d\n", ft_strncmp("123", "abc", 3));
// 	printf("%d\n", ft_strncmp("abcde", "ab", 3));
// 	printf("%d\n", ft_strncmp("a", "abc123", 3));
// 	printf("%d\n", strncmp("123", "abc", 3));
// 	printf("%d\n", strncmp("abcde", "ab", 3));
// 	printf("%d\n", strncmp("a", "abc123", 3));
// */
// }