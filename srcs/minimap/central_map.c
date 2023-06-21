/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susasaki <susasaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:20:00 by susasaki          #+#    #+#             */
/*   Updated: 2023/06/21 13:49:01 by susasaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	central_draw_one_block(t_data *data, int draw_x, int draw_y,
		int color)
{
	int	x;
	int	y;

	// (void)color;
	// (void)data;
	x = draw_x;
	while (x < draw_x + BLOCK_SIZE)
	{
		y = draw_y;
		while (y < (draw_y + BLOCK_SIZE))
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_check(t_info *info, int x, int y, int i, int j)
{
	(void)i;
	(void)j;
	// if (i == x && j == y)
	// {
	printf("xy = [%d][%d]\n", x, y);
	my_mlx_pixel_put(info->data, x, y, RED);
	// }
}

// void	draw_line_on_minimap(double pos_x, double pos_y, double end_x,
// 		double end_y, t_info *info)
// {
// 	int	x;
// 	int	y;
// 	int	i;
// 	int	j;
// 	x = pos_x;
// 	y = pos_y;
// 	i = 0;
// 	j = 0;
// 	printf("pos_x,end_x %d ~ %d\n", (int)pos_x, (int)end_x);
// 	printf("pos_y,end_y %d ~ %d\n", (int)pos_y, (int)end_y);
// 	while (i < WIN_WIDTH)
// 	{
// 		j = 0;
// 		while (j < WIN_HEIGHT)
// 		{
// 			x = pos_x;
// 			while (x < end_x)
// 			{
// 				y = pos_y;
// 				while (y < end_y)
// 				{
// 					draw_check(info, x, y, i, j);
// 					y++;
// 				}
// 				while (y > end_y)
// 				{
// 					draw_check(info, x, y, i, j);
// 					y--;
// 				}
// 				x++;
// 			}
// 			while (x > end_x)
// 			{
// 				y = pos_y;
// 				while (y < end_y)
// 				{
// 					draw_check(info, x, y, i, j);
// 					y++;
// 				}
// 				while (y > end_y)
// 				{
// 					draw_check(info, x, y, i, j);
// 					y--;
// 				}
// 				x--;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
void	player_draw_ray(t_info *info, t_vars *vars)
{
	double	x_direction;
	double	y_direction;
	double	line_length;
	double	end_x;
	double	end_y;
	int		mini_map_scale;

	// プレイヤーの現在位置と向きの取得
	x_direction = vars->x_direction;
	y_direction = vars->y_direction;

	mini_map_scale = mapdata_maxwidth_length(info->map);
	// 線の長さを計算（ここでは仮に10とする）
	line_length = 10;
	// 線の終点の座標を計算
	end_x = (info->player->pos_x + line_length * x_direction);
	end_y = (info->player->pos_y + line_length * y_direction);
	printf("dir_ %f,%f\n", x_direction, y_direction);
	printf("pos_ %f,%f\n", info->player->pos_x, info->player->pos_y);
	printf("end_ %f,%f\n", end_x, end_y);
	my_mlx_pixel_put(info->data, end_x, end_y, RED);
	// 描画関数を使用して線を描画
	// draw_line_on_minimap(info->player->pos_x, info->player->pos_y, end_x,
		// end_y,info);
}
void	central_map(t_info *info)
{
	/*
	map中央を求める
	mapの縦横の大きさか描画スタート地点を決める
	列ごとに描画する
	*/
	int x;
	int y;
	int start_x;
	int start_y;
	int end_x;
	int end_y;

	//描画開始地点を求める
	start_x = (WIN_WIDTH / 2) - ((mapdata_maxwidth_length(info->map)
			* BLOCK_SIZE) / 2);
	start_y = (WIN_HEIGHT / 2) - (((info->map->height) * BLOCK_SIZE) / 2);
	end_y = info->map->height;
	y = 0;

	// printf("start_x = %d\n",start_x);
	// printf("start_y = %d\n",start_y);
	// printf("end_y = %d\n",end_y);
	// printf("pos_vec [%f][%f]\n",
	// info->vars->x_direction,info->vars->y_direction);
	while (y < end_y)
	{
		x = 0;
		end_x = mapdata_width_length(info->map->map_data[y]);
		// printf("x = %d\n",x);
		// printf("end_x = %d\n",end_x);
		while (x < end_x + 1)
		{
			// printf("xy = [%d][%d]\n",x,y);
			// TODO: minimapのrayの描画ができていない
			if (info->map->map_data[y][x] == ' ')
			{
				;
			}
			// else if (info->map->map_data[y][x] == info->map->map_data\
			// [info->ray->current_y_in_map][info->ray->current_x_in_map])
			// {
			// 	central_draw_one_block(info->data, start_x + (x
			// * BLOCK_SIZE),
			// start_y + (y * BLOCK_SIZE), RED);
			// }
			else if (info->map->map_data[y][x] == '1'
				|| info->map->map_data[y][x] == '2'
				|| info->map->map_data[y][x] == '3'
				|| info->map->map_data[y][x] == '4')
			{
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), MAP_GREEN);
			}
			else if (info->map->map_data[y][x] == '0')
			{
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), MAP_WHITE);
			}
			else if (info->map->map_data[y][x] == 'N'
				|| info->map->map_data[y][x] == 'S'
				|| info->map->map_data[y][x] == 'E'
				|| info->map->map_data[y][x] == 'W')
			{
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), BLUE);
				info->player->pos_x = start_x + (x * BLOCK_SIZE / 2);
				info->player->pos_y = start_y + (y * BLOCK_SIZE / 2);
			}
			else
				central_draw_one_block(info->data, start_x + (x * BLOCK_SIZE),
					start_y + (y * BLOCK_SIZE), MAP_RED);
			x++;
		}
		y++;
	}

	// player_draw_ray(info, info->vars);
	return ;
}