/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:29:44 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 17:24:15 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_vector	*create_vector(float x, float y)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (vector == NULL)
	{
		write(STDERR_FILENO, "error: failed malloc.", 21);
		exit(1);
	}
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_vector	*add_vector(t_vector *a, t_vector *b)
{
	t_vector	*result;

	result = malloc(sizeof(t_vector));
	if (result == NULL)
	{
		write(STDERR_FILENO, "error: failed malloc.", 21);
		exit(1);
	}
	result->x = a->x + b->x;
	result->y = a->y + b->y;
	return (result);
}

t_vector	*sub_vector(t_vector *a, t_vector *b)
{
	t_vector	*result;

	result = malloc(sizeof(t_vector));
	if (result == NULL)
	{
		write(STDERR_FILENO, "error: failed malloc.", 21);
		exit(1);
	}
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	return (result);
}

t_vector	*multi_scalar_vector(t_vector *vector, float scalar)
{
	t_vector	*result;

	result = malloc(sizeof(t_vector));
	if (result == NULL)
	{
		write(STDERR_FILENO, "error: failed malloc.", 21);
		exit(1);
	}
	result->x = vector->x * scalar;
	result->y = vector->y * scalar;
	return (result);
}

float	magnitude_vector(t_vector *vector)
{
	return ((vector->x * vector->x) + (vector->y * vector->y));
}
