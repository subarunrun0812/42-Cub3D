/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 22:59:05 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/12 14:14:36 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ret;

	i = 0;
	if (size <= 0 && !dst && src)
		return (ft_strlen(src));
	while (*dst && i < size)
	{
		++dst;
		++i;
	}
	ret = ft_strlcpy(dst, src, size - i);
	return (ret + i);
}
// int		main(void)
// {
// 	char dst[10] = "ABCDEF";
// 	char src[] = "12345";

// 	size_t n = ft_strlcat(dst, src, 0);
// 	printf("dstの文字列は%s,戻り値は%zu", dst, n);
// 	return (0);
// }
