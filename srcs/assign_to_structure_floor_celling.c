/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_to_structure_floor_celling.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:49:35 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/30 18:38:37 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	assign_to_structure_floor(char **str, t_texture *texture)
{
	texture->f_tex = assign_to_structure(str,"floor",texture);
}

void	assign_to_structure_celling(char **str, t_texture *texture)
{
	texture->c_tex = assign_to_structure(str,"celling",texture);
}