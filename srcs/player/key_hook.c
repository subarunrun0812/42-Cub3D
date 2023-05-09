/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:44:58 by susasaki          #+#    #+#             */
/*   Updated: 2023/05/09 21:54:43 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int ft_key_hook(int keycode, t_vars *vars)
{
    if (keycode == W_KEY || keycode == S_KEY
        || keycode == A_KEY || keycode == D_KEY)
        ;
    else if (keycode == ESC_KEY)
        close_window(vars);
    return (0);
}