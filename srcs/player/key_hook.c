/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:44:58 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/14 22:29:23 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_key_hook(int keycode, t_info *info)
{
    // printf("~~ ft_key_hook ~~\n");
    // printf("keycode = %d", keycode);
    if (keycode == W_KEY || keycode == S_KEY
        || keycode == A_KEY || keycode == D_KEY)
    {
        player_move(info, keycode);
    }
    else if (keycode == ESC_KEY)
        close_window(info->vars);
    return (0);
}