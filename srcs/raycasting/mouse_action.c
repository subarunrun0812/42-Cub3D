/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/06 18:28:39 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_action(int mousecode, t_info *info)
{
	int	keycode;

	(void)info;
	if (mousecode == R_CLICK)
	{
		keycode = D_KEY;
	}
	else if (mousecode == L_CLICK)
	{
		keycode = A_KEY;
	}
	else
		return (-1);
	return (key_action(keycode, g_info));
}
