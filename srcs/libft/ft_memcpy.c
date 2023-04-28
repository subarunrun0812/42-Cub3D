/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:19:13 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/22 10:15:01 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_byte;
	const unsigned char	*src_byte;

	dst_byte = (unsigned char *)dst;
	src_byte = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dst_byte[i] = src_byte[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main(void)
// {
// 	// char buf[] = "ABCDDEFG";
// 	// char buf2[]= "123456789";

// 	char buf_[] = "ABCDEFG";
// 	char buf_2[] = "123456789";

// 	//3バイトだけコピー
// 	// memcpy(buf,buf2,3);
// 	ft_memcpy(buf_,buf_2,3);

// 	//表示
// 	// printf("コピー後のbuf文字列→%s\n",buf);
// 	printf("コピー後のbuf文字列→%s\n",buf_);

// 	return (0);
// 	//実行結果
// // コピー後のbuf文字列→123DEFG
// }