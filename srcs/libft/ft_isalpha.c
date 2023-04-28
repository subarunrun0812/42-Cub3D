/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:32:35 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/11 19:07:27 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	printf("%d",ft_isalpha('A'));
// 	printf("%s",ft_isalpha('5'));

// 	return (0);
// }