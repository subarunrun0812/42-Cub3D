/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:30:47 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/20 13:37:26 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
	}
}

// #include <stdio.h>

// static void	f(unsigned int i, char *s)
// {
// 	*s = *s + i;
// }

// int main(void)
// {
// 	char	str1[] = "abc";

// 	ft_striteri(str1, *f);
// 	printf("%s \n", str1);
// 	return (0);
// }