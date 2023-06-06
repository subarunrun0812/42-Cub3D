/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:49:19 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 15:20:11 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

#ifdef VECTOR

int	main(void)
{
	vector_2	*vector_1 = create_vector_2(10, 10);
	vector_2	*vector_2 = create_vector_2(5, 5);
	vector_2	*result = NULL;

	result = add_vector_2(vector_1, vector_2);
	printf(GREEN"+++++ add_vecotr_2(); +++++\n"END);
	printf("result->x : [%f]\n", result->x);
	printf("result->y : [%f]\n\n", result->y);

	free(result);
	result = sub_vector_2(vector_1, vector_2);
	printf(GREEN"+++++ sub_vecotr_2(); +++++\n"END);
	printf("result->x : [%f]\n", result->x);
	printf("result->y : [%f]\n\n", result->y);

	free(result);
	result = multi_scalar_vector_2(vector_1, 10);
	printf(GREEN"+++++ multi_scalar_vecotr_2(); +++++\n"END);
	printf("result->x : [%f]\n", result->x);
	printf("result->y : [%f]\n\n", result->y);


	float	magnitude;

	magnitude = magnitude_vector_2(result);
	printf(GREEN"+++++ magnitude_vecotr_2(); +++++\n"END);
	printf("magnitude : [%f]\n\n", magnitude);
}

#endif
