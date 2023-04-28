/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:37:19 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/15 14:59:15 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c += 'A' - 'a';
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main(void)
// {
// 	printf("a => %c\n", toupper('a'));
// 	printf("f => %c\n", toupper('f'));
// 	printf("A => %c\n", toupper('A'));
// 	printf("$ => %c\n", toupper('$'));

// 	return (0);
// }