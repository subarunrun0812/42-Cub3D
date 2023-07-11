/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/11 18:39:23 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_action(int mousecode, t_info *info)
{
	int	keycode;

	(void)info;
	if (mousecode == R_CLICK)
	{
		keycode = RIGHT_KEY;
	}
	else if (mousecode == L_CLICK)
	{
		keycode = LEFT_KEY;
	}
	else
		return (-1);
	return (key_action(keycode, g_info));
}
