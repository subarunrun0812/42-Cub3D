/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:30:19 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/21 10:57:27 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	nl;

	nl = n;
	if (nl == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	else if (nl < 0)
	{
		write(fd, "-", 1);
		nl *= -1;
	}
	if (nl >= 10)
	{
		ft_putnbr_fd(nl / 10, fd);
		ft_putnbr_fd(nl % 10, fd);
	}
	else
		ft_putchar_fd(nl + '0', fd);
}

// #include <fcntl.h>
// #include <limits.h>
// #include <stdio.h>
// #include <sys/stat.h>
// #include <sys/types.h>

// int	main(void)
// {
// 	int fd;
// 	int i = 2345;
// 	//int i = -42;
// 	fd = 1;
// 	//fd = open("./hoge.txt", O_RDWR);
// 	ft_putnbr_fd(i, fd);
// 	return (0);
// }