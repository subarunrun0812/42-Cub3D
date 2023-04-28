/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:47:26 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/11 19:10:01 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (len + 1 < size)
	{
		ft_memcpy(dst, src, len + 1);
	}
	else if (size > 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (len);
}
//why(size-1):https://ja.wikipedia.org/wiki/Strlcpy
// #include <stdio.h>
// #include <string.h>

// void test(int size)
// {
//     char string[] = "ABCDEFGHIJK";
//     char buffer[] = "1234567890";
//     int r;

//     r = ft_strlcpy(buffer,string,size);

//     printf("Copied '%s' into '%s', length %d\n",
//             string,
//             buffer,
//             r
//           );

// }

// int main()
// {
//     test(19);
//     test(10);
//     test(2);
//     test(1);
//     test(0);

//     return(0);
// }
