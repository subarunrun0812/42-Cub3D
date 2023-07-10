/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/07/10 11:44:34 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// valueの絶対値を返す関数
double	abs_double(double value)
{
	if (value == 0.0)
	{
		return (value);
	}
	if (value < 0)
	{
		value *= -1.0;
	}
	return (value);
}

static void	put_texture(t_draw_texture *texture, t_draw_wall *wall,
		t_info *info, int x_coordinate_screen)
{
	unsigned int	color;
	int				y_coordinate_screen;
	int				y_coordinate_texture;

	y_coordinate_screen = wall->start_y;
	while (y_coordinate_screen < wall->end_y)
	{
		// &(モジャロ演算)される。
		y_coordinate_texture
			= (int)texture->current_pos
			& (info->texture_list[texture->index].height
				- 1);
		texture->current_pos += texture->span;
		//addrは一次元配列なので、textureのaddress + height * y + x
		//で画像ファイルのメモリにアクセスでき、colorを指定できる
		color = *(info->texture_list[texture->index].data.addr
				+ info->texture_list[texture->index].height
				* y_coordinate_texture + texture->x_coord);
		if (wall->side == Y_AXIS)
		{
			color = (color >> 1) & 8355711;
		}
		//計算された色がスクリーンの正しい位置に配置する。
		info->data.addr[y_coordinate_screen * WIN_WIDTH
			+ x_coordinate_screen] = color;
		y_coordinate_screen += 1;
	}
}

static void	set_ray_data(t_ray *ray, t_vars *vars, int x)
{
	//画面上のpixel値(x座標)を視野の範囲に交換します
	double	x_current_cam;

	x_current_cam = 2 * x / (double)WIN_WIDTH - 1;
	//レイの方向 = カメラの向き + カメラ平面に対する現在の位置(x_current_cam)
	ray->x_dir = vars->x_dir + (vars->x_cam_plane
			* x_current_cam);
	ray->y_dir = vars->y_dir + (vars->y_cam_plane
			* x_current_cam);
	// プレイヤーの位置をマップ上の整数座標として設定する
	ray->x_map = (int)vars->x_pos;
	ray->y_map = (int)vars->y_pos;
	//初期化
	ray->x_side_dist = 0;
	ray->y_side_dist = 0;
	//もしレイがX方向に全く進まない(水平)な場合、x_delta_distは無限大として扱われるため、
	//それに近い1e30を設定する
	if (ray->x_dir == 0)
	{
		ray->x_delta_dist = 1e30;
	}
	else
	{
		// 水平に1グリッド進むのに必要な[実距離]を表す
		/*
		ブロックが正方形であり、そのサイズが1であるという仮定があります。
		レイのx方向とy方向の成分（ray->x_dirとray->y_dir）は、
		レイが1ユニット移動するときにx方向とy方向にそれぞれどれだけ移動するかを示しています。
		したがって、これらの値の逆数を取ると、レイがx方向またはy方向に1ユニット移動するために必要な距離が得られます。
		*/
		ray->x_delta_dist = abs_double(1 / ray->x_dir);
	}
	if (ray->y_dir == 0)
	{
		ray->y_delta_dist = 1e30;
	}
	else
	{
		// 垂直に1グリッド進むのに必要な[実距離]を表す
		ray->y_delta_dist = abs_double(1 / ray->y_dir);
	}
}

int	draw_wall(t_info *info)
{
	int				x_coordinate_screen;
	t_ray			ray;
	t_draw_wall		wall;
	t_draw_texture	texture;

	x_coordinate_screen = 0;
	while (x_coordinate_screen < WIN_WIDTH)
	{
		set_ray_data(&ray, &info->vars, x_coordinate_screen);
		set_draw_wall_data(&wall, &ray, info);
		set_draw_texture_data(&texture, &wall, &ray, info);
		put_texture(&texture, &wall, info, x_coordinate_screen);
		x_coordinate_screen += 1;
	}
	return (0);
}
