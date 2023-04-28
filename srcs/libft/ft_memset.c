/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:52:07 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/12 13:26:49 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t size)
{
	size_t			i;
	unsigned char	*dst_byte;
	unsigned char	c_byte;

	i = 0;
	dst_byte = (unsigned char *)dst;
	c_byte = (unsigned char)c;
	while (i < size)
	{
		dst_byte[i] = c_byte;
		i++;
	}
	return (dst);
}

// #include        <stdio.h>
// #include        <string.h>

// int main(void)
// {
//         char str[] = "0123456789";
// 		char str1[] = "0123456789";

//         memset(str+2, '*', 5);
//         ft_memset(str1+2, '*', 5);

//         printf("%s\n",str);
//         printf("%s\n",str1);

//         return (0);
// }
//【実行結果】
// 01*****789