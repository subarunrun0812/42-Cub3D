/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:46:13 by susasaki          #+#    #+#             */
/*   Updated: 2022/11/03 14:43:58 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

char	*ft_get_line(char *save);
char	*get_next_line(int fd);
char	*ft_read(int fd, char *save);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_strlen(char *str);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strdup(const char *s1);

#endif