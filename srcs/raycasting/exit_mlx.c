/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/08 14:07:16 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*exit_mlx_init(void)
{
	void	*mlx;

	mlx = mlx_init();
	if (mlx == NULL)
	{
		print_error("Failed malloc.");
	}
	return (mlx);
}

void	*exit_mlx_new_window(void *mlx)
{
	void	*window;

	window = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	if (window == NULL)
	{
		print_error("Failed malloc.");
	}
	return (window);
}

void	*exit_mlx_new_image(void *mlx)
{
	void	*image;

	image = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (image == NULL)
	{
		print_error("Failed malloc.");
	}
	return (image);
}