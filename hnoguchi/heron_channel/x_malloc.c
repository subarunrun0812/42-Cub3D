/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:25:54 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 14:31:07 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x_lib.h"

void*	x_malloc(size_t size)
{
	void	*memory;

	memory = malloc(size);
	if (memory == NULL)
	{
		fatal_error("error: failed malloc.");
	}
	return (memory);
}
