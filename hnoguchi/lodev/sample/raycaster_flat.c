/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_flat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 08:52:51 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/07 13:30:40 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

/*
#include "quickcg.h"
using namespace QuickCG;

g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

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

	x_position_vector_player = 22;
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
			 * doble	current_camera_x_coordinate;
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
			 * レイが居る現在のマップのマスの座標のみを表す。
			 *
			 * double	x_side_distance;
			 * double	y_side_distance;
			 * length of ray from current position to next x or y-side
			 * レイの開始位置から最初のxサイドと最初のyサイドまでの移動距離を初期値で指定する。
			 * コードの後半で、ステップを踏みながらインクリメントされる。
			 *
			 */
			double	x_current_camera; // cameraX;
			double	x_ray_direction; // rayDirX;
			double	y_ray_direction; // rayDirY;
			int		x_current_ray_in_map; // mapX
			int		y_current_ray_in_map; // mapY
			// TODO:
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
			double	deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
			double	deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h) drawEnd = h - 1;

      //choose wall color
      ColorRGB color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = RGB_Red;    break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }

      //give x and y sides different brightness
      if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color);
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
