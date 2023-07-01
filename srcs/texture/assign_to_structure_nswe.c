/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_to_structure_nswe.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:45:22 by susasaki          #+#    #+#             */
/*   Updated: 2023/07/01 13:40:58 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	assign_to_structure_no(char **str, t_texture *texture)
{
	texture->no = assign_to_structure(str,"no",texture);
}

void	assign_to_structure_so(char **str, t_texture *texture)
{
	texture->so = assign_to_structure(str,"so",texture);
}

void	assign_to_structure_we(char **str, t_texture *texture)
{
	texture->we = assign_to_structure(str,"we",texture);
}

void	assign_to_structure_ea(char **str, t_texture *texture)
{
	texture->ea = assign_to_structure(str,"ea",texture);
}
