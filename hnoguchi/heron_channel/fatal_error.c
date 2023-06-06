/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:31:16 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/06 14:32:41 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "x_lib.h"

void	fatal_error(const char *message)
{
	write(STDERR_FILENO, message, strlen(message));
	exit();
}
