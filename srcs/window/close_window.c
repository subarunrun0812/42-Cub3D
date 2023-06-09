/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:30:22 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/07 11:42:50 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	close_window(t_info *info)
{
	mlx_destroy_window(info->vars.mlx, info->vars.win);
	free_texture(info);
	exit(0);
}
