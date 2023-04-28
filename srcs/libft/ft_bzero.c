/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:39:14 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/18 22:46:22 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int     main(void)
// {
//     char    str1[] = "abcdefghi";
//     char    str2[] = "abcdefghi";
//     bzero(str1, 4);
//     printf("%c\n", *str1);
//     ft_bzero(str2, 4);
//     printf("%c\n", *str2);
// }
