/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:58:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/04/28 18:54:58 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../include/cub3d.h"

int main(int argc, char **argv)
{
    t_info info;
    if (argc != 2)
    {
        printf("Error:\nno map specified.\n");
    }
    init(&info);
    read_map(argv[1], &info);
}