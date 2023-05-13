/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:58:01 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/13 15:09:37 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../include/cub3d.h"

int main(int argc, char **argv)
{
    t_info info;
    t_vars vars;
    t_data data;
    
    if (argc != 2)
    {
        printf("\x1b[31mError:\nno map specified.\x1b[0m\n");
        return (0);
    }
    init(&info);
    read_map(argv[1], &info);
    player_coordinate(&info);
    new_window(&vars);
    
    data.img = mlx_new_image(&vars.mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
                                &data.endian);
    int x = WIN_WIDTH - 1;
    while (x > WIN_WIDTH - 201)
    {
        int y = 0;
        while (y < 200)
        {
            my_mlx_pixel_put(&data, x, y, 0x00FF0000);
            y++;
        }
        x--;
    }
    mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
    mlx_hook(vars.win, 2, 1L<<0, &ft_key_hook, &vars);
	mlx_hook(vars.win, ON_DESTROY, 1L << 2, &close_window, &vars);
    mlx_loop(vars.mlx);
}