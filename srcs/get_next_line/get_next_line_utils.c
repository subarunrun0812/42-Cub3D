/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:46:09 by susasaki          #+#    #+#             */
/*   Updated: 2022/11/03 13:42:28 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	char	*ans;

	if (s == NULL)
		return (NULL);
	ans = (char *)s;
	while (*ans != (char)c)
	{
		if (*ans == '\0')
			return (NULL);
		ans++;
	}
	return (ans);
}

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = size;
	if (!dst)
		return (len);
	size--;
	while (size-- && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}

char	*gnl_strdup(const char *s1)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (gnl_strlen((char *)s1) + 1));
	if (!str)
		return (NULL);
	gnl_strlcpy(str, s1, gnl_strlen((char *)s1) + 1);
	return (str);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL && s2 != NULL)
		return (gnl_strdup(s2));
	else if (s1 != NULL && s2 == NULL)
		return (gnl_strdup(s1));
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	dst = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len1)
		dst[i++] = *s1++;
	while (i < len1 + len2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return ((dst));
}
