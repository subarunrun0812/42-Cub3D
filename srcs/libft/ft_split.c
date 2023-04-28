/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 02:43:42 by susasaki          #+#    #+#             */
/*   Updated: 2022/10/22 10:26:15 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(char **str_p2, size_t listsize)
{
	size_t	i;

	i = 0;
	while (i < listsize)
		free(str_p2[i++]);
	free(str_p2);
}

size_t	len_string_division(const char *str_p1, char c)
{
	size_t	count;

	count = 0;
	while (str_p1[count] != c && str_p1[count] != '\0')
		count++;
	return (count);
}

size_t	count_words(const char *s1, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] == c)
			i++;
		if (s1[i] == '\0')
			break ;
		count++;
		while (s1[i] != c && s1[i] != '\0')
			i++;
	}
	return (count);
}

int	make_strlist(char **str_p2, const char *str_p1, char c)
{
	size_t	cnt;
	size_t	cntdiv;
	size_t	len;

	cnt = 0;
	cntdiv = 0;
	while (str_p1[cnt] != '\0')
	{
		while (str_p1[cnt] == c)
			cnt++;
		if (str_p1[cnt] == '\0')
			break ;
		len = len_string_division(&str_p1[cnt], c);
		str_p2[cntdiv] = (char *)malloc(sizeof(char) * (len + 1));
		if (!str_p2[cntdiv])
			return (0);
		ft_strlcpy(str_p2[cntdiv], &str_p1[cnt], len + 1);
		cntdiv++;
		cnt += len;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str_p2;
	size_t	count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	str_p2 = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str_p2)
		return (NULL);
	if (make_strlist(str_p2, s, c) == 0)
	{
		free_all(str_p2, count);
		return (NULL);
	}
	str_p2[count] = NULL;
	return (str_p2);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	string0[] = "      split       this for   me  !       ";
// 	char	**result0 =ft_split(string0, ' ');
// 	printf("%s\n", *result0);

// 	char	string1[] = "split  ||this|for|me|||||!|";
// 	char	**result1 =ft_split(string1, '|');
// 	printf("%s\n", *result1);

// 	// char	string3[50] = "This is correct";
// 	// char	**result3 =ft_split(string3, ' ');
// 	// printf("%s\n", *result3);

// 	return (0);
// }
/*

int	main(void)
{
	char	string[50];

	
	string[50] = "\0aa\0bbb";
	char** result = ft_split(string ,'\0');
	printf("%s\n",*result); //printing the token
	while (*result != NULL)
	{
	printf("%s\n",*result); //printing the token
	result++;
	}
	
	return (0);
}
// */