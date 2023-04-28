/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:34:10 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/28 17:32:55 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

static void filename_check(char *filename)
{
    char *cub;
    int     i;
    int     len;

    len = ft_strlen(filename);
    cub = ".cub";
    i = ft_strlen(cub);
    while (cub[i--] == filename[len--])
    {
        if (i == 0)
            break;
    }
    if (cub[i] != filename[len])
        print_error("filename");
    return ;
    
}

int read_map(char *path)
{
    int fd;
    // char *str;

    filename_check(path);
    fd = open(path, O_RDONLY);
    // if (fd == -1)
    //     print_error("open");
    // while(1)
    // {
    //     str = get_next_line(fd);
        
    // }
    return (TRUE);
}