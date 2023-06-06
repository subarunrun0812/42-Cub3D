/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:29:44 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 11:55:04 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

vector_2	create_vector_2(float x, float y)
{
	vector_2	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

vector_2	add_vector_2(vector_2 a, vector_2 b)
{
	vector_2	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;

	return (result);
}

vector_2	sub_vector_2(vector_2 a, vector_2 b)
{
	vector_2	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return (result);
}

vector_2	multi_scalar_vector_2(vector_2 vector, float scalar)
{
	vector_2	result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;

	return (result);
}

float	magnitude_vector_2(vector_2 vector)
{
	return ((vector.x * vector.x) + (vector.y * vector.y));
}
