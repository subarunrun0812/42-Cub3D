/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:38:10 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/22 10:51:02 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ans;

	ans = (char *)s;
	while (*ans != (char)c)
	{
		if (*ans == '\0')
			return (0);
		ans++;
	}
	return (ans);
}

// #include <string.h>
// #include <stdio.h>

// int main(void)
// {
// 	char str[] = "abcdefghijklmnabcdefghijklmn", *p;
// 	int c;

// 	printf("検索文字を入力してください。");
// 	c = getchar();

// 	p = ft_strchr(str, c);
// 	if (p != NULL) {
// 		printf("%cは文字列の%d番目にあります。\n", c, p - str);
// 		printf("以降の文字列は%sです。\n", p);
// 	}
// 	else
// 		printf("%cは見つかりませんでした\n", c);

// 	return (0);
// }
/*【実行結果例】
検索文字を入力してください。d
dは文字列の3番目にあります。
以降の文字列はdefghijklmnabcdefghijklmnです。
*/