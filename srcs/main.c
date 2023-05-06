/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:58:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/06 16:07:01 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../include/cub3d.h"

int main(int argc, char **argv)
{
    t_info info;
    if (argc != 2)
    {
        printf("\x1b[31mError:\nno map specified.\x1b[0m\n");
        return (0);
    }
    init(&info);
    read_map(argv[1], &info);
}