/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:49:19 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 18:27:05 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

#ifdef VECTOR

int	main(void)
{
	t_vector	*vector_1;
	t_vector	*vector_2;
	t_vector	*result;
	float		magnitude;

	vector_1 = create_vector(10, 10);
	vector_2 = create_vector(5, 5);
	result = add_vector(vector_1, vector_2);
	printf("vector_1 : x [%f], y [%f]\n", vector_1->x, vector_1->y);
	printf("vector_2 : x [%f], y [%f]\n", vector_2->x, vector_2->y);
	printf(GREEN"+++++ add_vecotr(); +++++\n"END);
	printf("result->x : [%f]\n", result->x);
	 printf("result->y : [%f]\n\n", result->y);
	free(result);
	result = sub_vector(vector_1, vector_2);
	printf(GREEN"+++++ sub_vecotr(); +++++\n"END);
	printf("result->x : [%f]\n", result->x);
	printf("result->y : [%f]\n\n", result->y);
	free(result);
	result = multi_scalar_vector(vector_1, 10);
	printf(GREEN"+++++ multi_scalar_vecotr(); +++++\n"END);
	printf("result->x : [%f]\n", result->x);
	printf("result->y : [%f]\n\n", result->y);
	free(result);
	magnitude = magnitude_vector(vector_1);
	printf(GREEN"+++++ magnitude_vecotr(); +++++\n"END);
	printf("magnitude : [%f]\n\n", magnitude);
	free(vector_1);
	free(vector_2);
}

#elif RAY

int	main(void)
{
	t_vector	*vector_1;
	t_vector	*vector_2;
	t_ray		*ray;
	t_vector	*result;

	vector_1 = create_vector(10, 10);
	vector_2 = create_vector(5, 5);
	ray = create_ray(vector_1, vector_2);
	result = point_at_ray(ray, 15);

	printf("vector_1 : x [%f], y [%f]\n", vector_1->x, vector_1->y);
	printf("vector_2 : x [%f], y [%f]\n\n", vector_2->x, vector_2->y);

	printf(GREEN"+++++ create_ray(); +++++\n"END);
	printf("ray->start_point->x [%f]\n", ray->start_point->x);
	printf("ray->start_point->y [%f]\n\n", ray->start_point->y);

	printf("ray->direction->x [%f]\n", ray->direction->x);
	printf("ray->direction->y [%f]\n\n", ray->direction->y);

	printf(GREEN"+++++ point_at_ray(); +++++\n"END);
	printf("result->x : [%f]\n", result->x);
	printf("result->y : [%f]\n\n", result->y);

	free(result);
	free(vector_1);
	free(vector_2);
	free(ray);
}

#endif
