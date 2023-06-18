/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_textured.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:33:56 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/16 18:15:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define texture_width 64
#define texture_height 64
#define TEXTURE_LIST_SIZE 10;
int	world_map[MAP_WIDTH][MAP_HEIGHT]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

Uint32 buffer[WIN_HEIGHT][WIN_WIDTH];

int main(int /*argc*/, char */*argv*/[])
{
	double posX = 22.0, posY = 11.5;  //x and y start position
	double dirX = -1.0, dirY = 0.0; //initial direction vector
	double planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane
	
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	// 64 * 64のテクスチャ配列[8][4096]
	// std::vector<Uint32> texture[8];
	// for(int i = 0; i < 8; i++)
	// {
	//	texture[i].resize(texture_width * texture_height);
	// }
	// screen(screenWidth,screenHeight, 0, "Raycaster");
	
	// テクスチャの生成を行う。//generate some textures
#if 0
	unsigned int	texture_list[8][texutre_width * texture_height];
	int				x;
	int				y;
	
	x = 0;
	y = 0;
	while (x < texture_width)
	{
		while (y < texture_height)
		{
			int	xor_color;
			// int	x_color;
			int	y_color;
			int	x_y_color;
			
			xor_color = (x * 256 / texture_width) ^ (y * 256 / texture_height);
			// x_color = x * 256 / texture_width;
			y_color = y * 256 / texture_height;
			x_y_color = y * 128 / texture_height + x * 128 / texture_width;
 
			//flat red texture with black cross
			texture_list[0][texture_width * y + x] = 65536 * 254 * (x != y && x != texture_width - y);

			//sloped greyscale
			texture_list[1][texture_width * y + x] = x_y_color + 256 * x_y_color + 65536 * x_y_color;

			//sloped yellow gradient
			texture_list[2][texture_width * y + x] = 256 * x_y_color + 65536 * x_y_color;

			//xor greyscale
			texture_list[3][texture_width * y + x] = xor_color + 256 * xor_color + 65536 * xor_color;

			//xor green
			texture_list[4][texture_width * y + x] = 256 * xor_color;

			//red bricks
			texture_list[5][texture_width * y + x] = 65536 * 192 * (x % 16 && y % 16);

			//red gradient
			texture_list[6][texture_width * y + x] = 65536 * y_color;

			//flat grey texture
			texture_list[7][texture_width * y + x] = 128 + 256 * 128 + 65536 * 128;
			y += 1;
		}
		y = 0;
		x += 1;
  }
#else
	// generate some textures
	void		*texture_list[TEXTURE_LIST_SIZE];
	static char	*texture_path_list[TEXTURE_LIST_SIZE] = {
		"./xpm/nature.xpm",
		"./xpm/bluestone.xpm",
		"./xpm/colorstone.xpm",
		"./xpm/eagle.xpm",
     	"./xpm/greenlight.xpm",
     	"./xpm/greystone.xpm",
     	"./xpm/mossy.xpm",
     	"./xpm/pillar.xpm",
     	"./xpm/redbrick.xpm",
     	"./xpm/wood.xpm
	};
	int			texture_width[TEXTURE_LIST_SIZE];
	int			texture_height[TEXTURE_LIST_SIZE];
	int			i;

	i = 0;
	while (i < TEXTURE_LIST_SIZE)
	{
		texture_list[i] = mlx_xpm_file_to_image(vars.mlx, texture_path_list[i], &texture_width[i], &texture_height[i]);
		i += 1;
	}
	// loadImage(texture[0], tw, th, "pics/eagle.png");
	// loadImage(texture[1], tw, th, "pics/redbrick.png");
	// loadImage(texture[2], tw, th, "pics/purplestone.png");
	// loadImage(texture[3], tw, th, "pics/greystone.png");
	// loadImage(texture[4], tw, th, "pics/bluestone.png");
	// loadImage(texture[5], tw, th, "pics/mossy.png");
	// loadImage(texture[6], tw, th, "pics/wood.png");
	// loadImage(texture[7], tw, th, "pics/colorstone.png");
#endif

  //start the main loop
  while(!done())
  {
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX*cameraX;
      double rayDirY = dirY + planeY*cameraX;

      //which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
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
      while (hit == 0)
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

      //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

	 
	  // TODO: START difference.
	  int pitch = 100;

      //calculate lowest and highest pixel to fill in current stripe
	  // draw_line();
      int	draw_start;
      int	draw_end;

      draw_start = (-line_height / 2) + (screen_height / 2) + pitch;
      if(draw_start < 0)
	  {
		  draw_start = 0;
	  }
      draw_end = (line_height / 2) + (h / 2) + pitch;
      if(h <= draw_end)
	  {
		  draw_end = h - 1;
	  }
	  // texturing calculations
	  // 1 subtracted from it so that texture 0 can be used!
	  // int texNum = worldMap[mapX][mapY] - 1;
	  int texture_number = world_map[ray->current_x_in_map][ray->current_y_in_map] - 1;

      //calculate value of wallX wall_x
      // double wallX; //where exactly the wall was hit
      double	wall_x; //where exactly the wall was hit
	  if(side == 0) 
	  {
		  // wallX = posY + perpWallDist * rayDirY;
		  wall_x = vars->y_position_vector + perpendicular_wall_distance * ray->y_direction;
	  }
	  else
	  {
		  // wallX = posX + perpWallDist * rayDirX;
		  wall_x = vars->x_position_vector + perpendicular_wall_distance * ray->x_direction;
	  }
	  // double	floor(double x);
	  // ¸引数x以下で最大の整数値を得る
      // wallX -= floor((wallX));
      wall_x = floor((wallX));

      //x coordinate on the texture
      // int texX = int(wallX * double(texWidth));
      int texture_x;

      texture_x = (int)(wall_x * (double)texture_width);
      // if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      // if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
      if (side == 0 && 0 < ray->x_direction)
	  {
		  texture_x = texture_width - texture_x - 1;
	  }
	  if (side == 1 && ray->y_direction < 0)
	  {
		  texture_x = texture_width - texture_x - 1;
	  }
      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      // double step = 1.0 * texHeight / lineHeight;
      double	step;

      step = (1.0 * texture_height) / line_height;
      // Starting texture coordinate
      // double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
      double	texture_position;

      texture_position = (draw_start - pitch - h / 2 + line_height / 2) * step;
	  int	y;

	  y = draw_start;
      while (y < draw_end)
	  {
		  // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		  // int texY = (int)texPos & (texHeight - 1);
		  int	texture_y;

		  texture_y = (int)texture_position & (texture_height - 1);
		  texture_position += step;
		  // Uint32 color = texture[texNum][texHeight * texY + texX];
		  unsigned int	color;

		  color = texture_list[texture_number][texture_height * texture_y + texture_x];
		  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		  /*
		   * Because of this, the last bit of one byte will become the first bit of the next byte,
		   * and that screws up the color values!
		   * So after the bitshift, the first bit of every byte has to be set to zero,
		   * and that can be done by binary "AND-ing" the value with the binary value 011111110111111101111111,
		   * which is 8355711 in decimal.
		   * So the result of this is indeed a darker color.
		   */
		  if (side == 1)
		  {
			  color = (color >> 1) & 8355711;
		  }
		  buffer[y][x] = color;
		  y += 1;
	  }
	}
    drawBuffer(buffer[0]);
    for(int y = 0; y < h; y++)
	{
		for(int x = 0; x < w; x++)
		{
			buffer[y][x] = 0; //clear the buffer instead of cls()
		}
	}
    //timing for input and FPS counter
    oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
    redraw();

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
    if(keyDown(SDLK_ESCAPE))
    {
      break;
    }
  }
}
