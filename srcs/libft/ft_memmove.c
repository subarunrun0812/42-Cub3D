/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:31:47 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/21 16:01:13 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_byte;
	unsigned char	*src_byte;

	dst_byte = (unsigned char *)dst;
	src_byte = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (src < dst)
	{
		while (len)
		{
			*(dst_byte + len - 1) = *(src_byte + len - 1);
			len--;
		}
	}
	else
	{
		while (len--)
			*(dst_byte++) = *(src_byte++);
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char	b[0xF0];
// 	size_t	test14;

// 	puts("----ft_memmove------");
// 	char* test11 = b;
// 	char* test12 = b;
// 	char* test13 = NULL;
// 	test14 = 5;
// 	ft_memmove(b, NULL, 5);
// 	// memmove(test12, test13, test14);
// 	// char    test21[] = "abcde";
// 	// char    test22[] = "abcde";
// 	// char    test23[] = "1 3 5";
// 	// size_t    test24 = 4;
// 	// ft_memmove(test21, test23, test24);
// 	// memmove(test22, test23, test24);
// 	// const char    test31[] = "123\n";
// 	printf("zisaku  : %s\nlibrary : %s\n\n", test11, test12);
// 	// printf("zisaku  : %s\nlibrary : %s\n\n", test21, test22);
// }
