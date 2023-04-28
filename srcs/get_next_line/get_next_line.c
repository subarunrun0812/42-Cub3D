/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:46:05 by susasaki          #+#    #+#             */
/*   Updated: 2022/11/05 15:37:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *save)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = (char *)malloc((gnl_strlen(save) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}

char	*ft_get_line(char *save)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = 0;
	i = 0;
	while (save[len] && save[len] != '\n')
		len++;
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read(int fd, char *save)
{
	char	*buf;
	int		count;
	char	*tmp;

	count = 1;
	buf = malloc(sizeof(char) * ((unsigned int)BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!gnl_strchr(save, '\n') && count != 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[count] = '\0';
		tmp = gnl_strjoin(save, buf);
		free(save);
		save = tmp;
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read(fd, save);
	if (save == NULL || *save == '\0')
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = ft_get_line(save);
	save = ft_save(save);
	return (line);
}
