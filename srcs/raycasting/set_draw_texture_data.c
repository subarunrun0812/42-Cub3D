/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_draw_texture_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/09 15:46:26 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//壁の東西南北のテクスチャの決定
static int	decide_draw_texture(t_ray *ray, t_vars *vars, int side)
{
	if (side == Y_AXIS)
	{
		if (ray->y_map < vars->y_pos)
		{
			return (WEST_WALL);
		}
		return (EAST_WALL);
	}
	else if (ray->x_map < vars->x_pos)
	{
		return (NORTH_WALL);
	}
	return (SOUTH_WALL);
}

static double	get_hit_wall_x(t_draw_wall *wall, t_ray *ray, t_vars *vars)
{
	double	wall_x;

	wall_x = 0.0;
	// 衝突したのが、X軸の整数値の場合
	if (wall->side == X_AXIS)
	{
		wall_x = vars->y_pos + wall->wall_dist
			* ray->y_dir;
	}
	else
	{
		wall_x = vars->x_pos + wall->wall_dist
			* ray->x_dir;
	}
	//計算された壁の座標から整数部分を除き、壁の座標を0.0から1.0の範囲に正規化する。
	//この結果は、テクスチャのどの部分が壁の表面に描画されるべきかを決定するために使用される。
	wall_x -= floor((wall_x));
	return (wall_x);
}

static int	get_x_coordinate_texture(t_draw_texture *texture, t_draw_wall *wall,
		t_ray *ray, t_info *info)
{
	int	x_coord_texture;

	x_coord_texture = (int)(texture->wall_x
			* (double)info->texture_list[texture->index].width);
	//テクスチャのピクセルを右端から左端に向かって読み取るのを反転する
	if (wall->side == 0 && 0 < ray->x_dir)
	{
		x_coord_texture = info->texture_list[texture->index].width
			- x_coord_texture - 1;
	}
	//テクスチャのピクセルを下端から上端に向かって読み取るのを反転する
	if (wall->side == 1 && ray->y_dir < 0)
	{
		x_coord_texture = info->texture_list[texture->index].width
			- x_coord_texture - 1;
	}
	return (x_coord_texture);
}

void	set_draw_texture_data(t_draw_texture *texture, t_draw_wall *wall,
		t_ray *ray, t_info *info)
{
	texture->index = decide_draw_texture(ray, &info->vars, wall->side);
	texture->wall_x = get_hit_wall_x(wall, ray, &info->vars);
	texture->x_coord = get_x_coordinate_texture(texture, wall, ray, info);
	texture->span = (1.0 * info->texture_list[texture->index].height)
		/ wall->line_height;
	texture->current_pos = (wall->start_y - (WIN_HEIGHT / 2)
			+ (wall->line_height / 2)) * texture->span;
}
