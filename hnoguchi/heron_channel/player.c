/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:38:07 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 14:51:30 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_player	*create_player(float vector_x, float vector_y, float player_angle)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (player == NULL)
	{
		write(STDERR_FILENO, "error: failed malloc.", 21);
		exit(1);
	}
	player->position->x = vector_x;
	player->position->y = vector_y;
	player->angle = player_angle;
	return (player);
}

void	move_player(t_player *player,  float direction_x, float direction_y)
{
	player->position->x += direction_x;
	player->position->y += direction_y;
}

void	rotate_player(t_player *player, float angle)
{
	player->angle += angle;
}
