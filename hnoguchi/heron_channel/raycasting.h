/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:30:28 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 18:12:45 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "color.h"

typedef struct s_vector	t_vector;
typedef struct s_ray	t_ray;
typedef struct s_player	t_player;

struct s_vector {
	float	x;
	float	y;
};

struct s_ray {
	t_vector	*start_point;
	t_vector	*direction;
};

struct s_player {
	t_vector 	*position;
	float		angle;
};

// Vector
t_vector	*create_vector(float x, float y);
t_vector	*add_vector(t_vector *a, t_vector *b);
t_vector	*sub_vector(t_vector *a, t_vector *b);
t_vector	*multi_scalar_vector(t_vector *vector, float scalar);
float		magnitude_vector(t_vector *vector);

// Ray
t_ray		*create_ray(t_vector *start_p, t_vector *direction);
t_vector	*point_at_ray(t_ray *ray, float t);

// Player
t_player	*create_player(float vector_x, float vector_y, float player_angle);
void		move_player(t_player *player,  float direction_x, float dorection_y);
void		rotate_player(t_player *player, float angle);

#endif
