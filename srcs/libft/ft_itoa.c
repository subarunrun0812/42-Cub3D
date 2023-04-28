/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 02:43:46 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/21 19:09:05 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	digit_len(long long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		len;
	long long	nl;

	nl = n;
	len = digit_len(nl);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (nl < 0)
	{
		str[0] = '-';
		nl *= -1;
	}
	else if (nl == 0)
		str[0] = '0';
	while (nl > 0)
	{
		str[len] = nl % 10 + '0';
		nl /= 10;
		len--;
	}
	return (str);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	// printf("%s\n", ft_itoa(0));
	// printf("%s\n", ft_itoa(1));
	// printf("%s\n", ft_itoa(-1));
	// printf("%s\n", ft_itoa(15));
	// printf("%s\n", ft_itoa(-15));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(9999999999));
	printf("%s\n", ft_itoa(-9999999999));
}
*/