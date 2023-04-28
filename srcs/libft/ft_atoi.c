/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:58:05 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/23 12:04:22 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	long	res;
	int		neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return ((int)(res * neg));
}
// #include <stdlib.h>
// #include <stdio.h>
// #include <limits.h>

// int	main(void)
// {
// 	// printf("LONG_MAX : %lu : INT_MAX : %d\n", LONG_MAX, INT_MAX);
// 	printf("%d : %d\n", atoi("9"), ft_atoi("9"));
// 	printf("%d : %d\n", atoi("0"), ft_atoi("0"));
// 	printf("%d : %d\n", atoi("4500"), ft_atoi("4500"));
// 	printf("%d : %d\n", atoi("43a"), ft_atoi("43a"));
// 	printf("%d : %d\n", atoi("+50"), ft_atoi("+50"));
// 	printf("%d :%d\n", atoi("-943"), ft_atoi("-943"));
// 	return (0);
// }