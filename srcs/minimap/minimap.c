/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 22:32:42 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/13 15:11:07 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3d.h"

int minimap(t_info *info)
{
    printf("map->height = %d\n",info->map->height);
    // t_data data;
    // //minimapの画像表示
    // data.img = mlx_new_image(info->vars->mlx, WIN_WIDTH, WIN_HEIGHT);
    // data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
    //                             &data.endian);
    // int x = WIN_WIDTH - 1;
    // while (x > WIN_WIDTH - 201)
    // {
    //     int y = 0;
    //     while (y < 200)
    //     {
    //         my_mlx_pixel_put(&data, x, y, 0x00FF0000);
    //         y++;
    //     }
    //     x--;
    // }
    // mlx_put_image_to_window(info->vars->mlx, info->vars->win, data.img, 0, 0);

    return (0);
}
