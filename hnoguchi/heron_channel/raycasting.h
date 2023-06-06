/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:30:28 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 11:55:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include <stdio.h>
#include <math.h>

typedef struct vector_2 {
	float	x;
	float	y;
}	vector_2;

typedef struct ray_2 {
	vector_2	start_point;
	vector_2	direction;
}	ray_2;

typedef struct s_player {
	vector_2 	position;
	float	angle;
}	t_player;

// Vector
vector_2	create_vector_2(float x, float y);
vector_2	add_vector_2(vector_2 a, vector_2 b);
vector_2	sub_vector_2(vector_2 a, vector_2 b);
vector_2	multi_scalar_vector_2(vector_2 vector, float scalar);
float		magnitude_vector_2(vector_2 vector);

// Ray
ray_2		create_ray_2(vector_2 start_p, vector_2 direction);
vector_2	point_at_ray_2(ray_2 ray, float t);

// Player
t_player	create_player(float vector_x, float vector_y, float player_angle);
void		move_player(t_player *player,  float direction_x, float dorection_y);
void		rotate_player(t_player *player, float angle);

#endif
