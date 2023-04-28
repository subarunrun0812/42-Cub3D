/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:11:16 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/22 10:51:49 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*ans;

	ans = (unsigned char *)s;
	while (n--)
	{
		if (*(unsigned char *)ans == (unsigned char)c)
			return (ans);
		ans++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*p;

// 	char str[] = "abcdef\0ghij"; /* 途中に空文字のある文字列 */
// 	p = ft_memchr(str, 'h', 10);
// 	printf("検索文字は文字列の%d番目\n", p - str);
// 	return (0);
// }

//【実行結果】
//検索文字は文字列の8番目