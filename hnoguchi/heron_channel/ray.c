/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:36:04 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 17:59:36 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_ray	*create_ray(t_vector *start_p, t_vector *direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
	{
		write(STDERR_FILENO, "error: failed malloc.", 21);
		exit(1);
	}
	ray->start_point = start_p;
	ray->direction = direction;
	return (ray);
}

t_vector	*point_at_ray(t_ray *ray, float t)
{
	t_vector	*point;
	
	point = add_vector(ray->start_point, multi_scalar_vector(ray->direction, t));
	return (point);
}
