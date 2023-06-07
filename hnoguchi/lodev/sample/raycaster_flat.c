/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:52:51 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/07 18:44:22 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <vector>
// #include <iostream>

/*
#include "quickcg.h"
using namespace QuickCG;

g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

typedef enum e_color_rgb	t_color_rgb;
enum e_color_rgb {
	RGB_Red,
	RGB_Green,
	RGB_Blue,
	RGB_White,
	RGB_Yellow
};

//place the example code below here:

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define ABS(a) ((a) < 0 ? -(a) : (a))

int world_map[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// int main(int /*argc*/, char /*argv*/[])
int	main(void)
{
	/*
	 * camera_palane が direction に対して垂直であることを確認する。camera_plane の長さは変更が可能。
	 *
	 * current_time_frame, old_time_frame
	 * この２つの時間差は、特定のキーが押されたときに、どれくらい動くべきかを決定する。
	 * （フレームの計算にどれだけ時間が掛かっても、一定の速度で動くため）
	 * およびFPSカウンターのために使用できる。
	 */

	double	x_position_vector_player; // player position vector
	double	y_position_vector_player; // player position vector
	double	x_direction_player; // initial player direction vector
	double	y_direction_player; // initial player direction vector
	double	x_camera_plane_player; //the 2d raycaster version of camera plane of the player
	double	y_camera_plane_player; //the 2d raycaster version of camera plane of the player
	double	current_time_frame; //time of current frame
	double	old_time_frame; //time of previous frame

	x_position_vector_player = 22; // posX
	y_position_vector_player = 12;
	x_direction_player = -1;
	y_direction_player = 0;
	x_camera_plane_player = 0;
	y_camera_plane_player = 0.66;
	current_time_frame = 0;
	old_time_frame = 0;

	// screen();
	// 画面の設定を行う関数
	screen(screenWidth, screenHeight, 0, "Raycaster");
	// done();
	// フレーム全体の描画と、毎回入力を読み取るループ。
	while(!done())
	{
		// raycasting loop
		/*
		 * レイキャスティングループは、すべてのxを通過するforループなので、画面のすべてのピクセルに対して計算があるわけではなく、
		 * 縦のストライプに対してだけで、全然多くないです！
		 * レイキャスティングループを開始するために、いくつかの変数がデリケートで計算されます：
		 *
		 * ¸光線上のみ計算を行う。。。？？
		 * int	x = 0;
		 * x¸座標のこと。横軸
		 * 
		 * int w;
		 * 未定義？？多分マップの横幅？？
		 *
		 * ray ¸の始点は、x_position_vector_player, y_position_vector_player
		 */
		for(int x = 0; x < w; x++)
		{
			//calculate ray position and direction
			//x-coordinate in camera space
			/*
			 * doble	current_camera_x;
			 * 現在の画面のx座標にあるカメラ平面上のx 座標を表す。
			 * 画面の左側が、−１。中央が０。右側が、１。となる。
			 *
			 * double	x_ray_direction;
			 * double	y_ray_direction;
			 * 光線の方向を表す。
			 * プレイヤーの方向ベクトル( _direction_player)とカメラの平面ベクトル¸の一部( _camera_plane_player * x_current_camera)の和として計算できる。)
			 * (x座標とy座標の両方について¸計算を行う必要がある。)
			 *
			 * int	x_current_ray_in_map;
			 * int	y_current_ray_in_map;
			 * which box of the map we're in
			 * レイが居る現在のマップのマスの座標のみを表す。レイとマスの交点？？
			 *
			 * double	x_side_distance;
			 * double	y_side_distance;
			 * length of ray from current position to next x or y-side
			 * レイの開始位置から最初のxサイドと最初のyサイドまでの移動距離を初期値で指定する。
			 * コードの後半で、ステップを踏みながらインクリメントされる。
			 *
			 * double	x_delta_distance;
			 * double	y_delta_distance;
			 * レイが座標１つ分を移動する際の距離を表す。
			 *
			 * double perpendicular_wall_distance;
			 * 壁からレイまでの長さを入れる変数。
			 * 壁の高さを計算するのに使用する。
			 *
			 * int	step_x;
			 * int	step_y;
			 * what direction to step in x or y-direction (either +1 or -1)
			 * direction(x, y)¸の方向（プラスかマイナスか）を示す変数。−１か１が入る。
			 * 負の成分を持っている場合、−１。それ以外は、１を入れる。
			 *
			 * int	x_side_distance;
			 * int	y_side_distance;
			 * step_x¸が−１の場合、レイの開始位置から左側の最初の軸までの距離を入れる。
			 * step_xが、+1¸の場合、右側の最初の軸までの距離を入れる。 
			 * step_y¸が−１の場合、レイの開始位置から¸上側の最初の軸までの距離を入れる。
			 * step_y¸が+１の場合、レイの開始位置から¸下側の最初の軸までの距離を入れる。
			 *
			 * int hit;
			 * was there a wall hit?
			 * ループを抜けるかどうかの判定に使用する変数
			 * 壁に当たったかどうか？？
			 *
			 * int side;
			 * was a NS or a EW wall hit?
			 * どの方角の壁にぶつかったか？？
			 * x軸なら０。y軸なら１。
			 *
			 *
			 * */

			double	x_current_camera; // cameraX;
			double	x_ray_direction; // rayDirX;
			double	y_ray_direction; // rayDirY;
			int		x_current_ray_in_map; // mapX
			int		y_current_ray_in_map; // mapY
			// TODO: Set initialize value.
			double	x_side_distance; // sideDistX;
			double	y_side_distance; // sideDistY;

			x_current_camera = 2 * x / (double)w - 1;
			x_ray_direction = x_direction_player + (x_camera_plane_player * x_current_camera); // = dirX + planeX * cameraX;
			y_ray_direction = y_direction_player + (y_camera_plane_player * x_current_camera); // = dirY + planeY * cameraX;
			x_current_ray_in_map = int(x_position_vector_player); // = int(x_posX);
			y_current_ray_in_map = int(y_position_vector_player); // = int(posY);
			// length of ray from one x or y-side to next x or y-side
			// these are derived as:
			// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      		// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      		// which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      		// where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      		// unlike (dirX, dirY) is not 1, however this does not matter, only the
      		// ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      		// stepping further below works. So the values can be computed as below.
      		// Division through zero is prevented, even though technically that's not
      		// needed in C++ with IEEE 754 floating point values.
			double	x_delta_distance; // deltaDistX
			double	y_delta_distance; // deltaDistY

			// ¸ゼロ除算を回避する。（ゼロの場合は、非常に大きい値を設定する。）
			x_delta_distance = (x_ray_direction == 0) ? 1e30 : ABS(1 / x_ray_direction); // deltaDistX
			y_delta_distance = (y_ray_direction == 0) ? 1e30 : ABS(1 / y_ray_direction); // deltaDistY
			
			double perpendicular_wall_distance;

			int	step_x; // stepX
			int	step_y; // stepY
			int hit;
			int side;

			hit = 0;
			//calculate step_x(or y) and initial x(or y)_side_distance
			if(x_ray_direction < 0)
			{
				step_x = -1;
				x_side_distance = (x_position_vector_player - x_current_ray_in_map) * x_delta_distance;
			}
			else
			{
				step_x = 1;
				x_side_distance = (x_current_ray_in_map + 1.0 - x_position_vector_player) * x_delta_distance;
			}
			if(y_ray_direction < 0)
			{
				step_y = -1;
				y_side_distance = (y_position_vector_player - y_current_ray_in_map) * y_delta_distance;
			}
			else
			{
				step_y = 1;
				y_side_distance = (y_current_ray_in_map + 1.0 - y_position_vector_player) * y_delta_distance;
			}
			//perform DDA
			while(hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if(x_side_distance < y_side_distance)
				{
					x_side_distance += x_delta_distance;
					x_current_ray_in_map += step_x;
					side = 0;
				}
				else
				{
					y_side_distance += y_delta_distance;
					y_current_ray_in_map += step_y;
					side = 1;
				}
				//Check if ray has hit a wall
				if(world_map[x_current_ray_in_map][y_current_ray_in_map] > 0)
				{
					hit = 1;
				}
			}
			// Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
			// hit to the camera plane. Euclidean to center camera point would give fisheye effect!
			// This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
			// for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
			// because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
			// steps, but we subtract deltaDist once because one step more into the wall was taken above.
			if(side == 0)
			{
				perpendicular_wall_distance = (x_side_distance - x_delta_distance);
			}
			else
			{
				perpendicular_wall_distance = (y_side_distance - y_delta_distance);
			}
			//Calculate height of line to draw on screen
			/*
			 * h
			 * 画面の高さ（ピクセル単位）
			 * ピクセル座標に変換する際に使用する。
			 */
			int	line_height;
			
			line_height = (int)(h / perpendicular_wall_distance);
			// calculate lowest and highest pixel to fill in current stripe
			int draw_start;
			
			draw_start = -line_height / 2 + h / 2;
			if(draw_start < 0)
			{
				draw_start = 0;
			}
			
			int draw_end;
			
			draw_end = line_height / 2 + h / 2;
			if(draw_end >= h)
			{
				draw_end = h - 1;
			}
			// choose wall color

			t_color_rgb	 color;
			switch(world_map[x_current_ray_in_map][y_current_ray_in_map])
			{
				case 1:
					color = RGB_Red;
					break; //red
				case 2:
					color = RGB_Green;
					break; //green
				case 3:
					color = RGB_Blue;
					break; //blue
				case 4:
					color = RGB_White;
					break; //white
				default:
					color = RGB_Yellow;
					break; //yellow
			}
			//give x and y sides different brightness
			if (side == 1)
			{
				color = color / 2;
			}
			//draw the pixels of the stripe as a vertical line
			if (color == RGB_Red)
			{
				// "red" == 0xff0000
				verLine(x, drawStart, drawEnd, color);
			}
			else if (color == RGB_Green)
			{
				// "green" == 0xff00
				verLine(x, drawStart, drawEnd, color);
			}
			else if (color == RGB_Blue)
			{
				// "blue" == 0xff
				verLine(x, drawStart, drawEnd, color);
			}
			else if (color == RGB_White)
			{
				// "white" == 0xffffff
				verLine(x, drawStart, drawEnd, color);
			}
			else if (color == RGB_Yellow)
			{
				// "yellow" == 0xffff00
				verLine(x, drawStart, drawEnd, color);
			}
		}
	//timing for input and FPS counter
	oldTime = time;
	time = getTicks();
	double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
    redraw();
    cls();

    //speed modifiers
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    readKeys();
    //move forward if no wall in front of you
    if(keyDown(SDLK_UP))
    {
      if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if(keyDown(SDLK_DOWN))
    {
      if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if(keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if(keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
  }
}
