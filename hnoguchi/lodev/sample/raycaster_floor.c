/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:14:40 by hnoguchi          #+#    #+#             */
/*   Updated: 2023/06/22 15:56:17 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int world_map[MAP_WIDTH][MAP_HEIGHT] =
{
  {8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
  {8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
  {8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
  {8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
  {7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
  {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
  {7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
  {7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
  {2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
  {2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
  {1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
  {2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
  {2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
  {2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
  {2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
};

#if FLOOR_HORIZONTAL
    //FLOOR CASTING
	int	y;

	y = (vars->screen_height / 2) + 1;
    while (y < vars->screen_height)
    {
		y += 1;
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float	x_ray_direction_0 = vars->x_direction - vars->x_camera_plane; // float	rayDirX0 = dirX - planeX;
		float	y_ray_direction_0 = vars->y_direction - vars->y_camera_plane; // float	rayDirY0 = dirY - planeY;
		float	x_ray_direction_1 = vars->x_direction + vars->x_camera_plane; // float	rayDirX1 = dirX + planeX;
		float	y_ray_direction_1 = vars->y_direction + vars->y_camera_plane; // float	rayDirY1 = dirY + planeY;
		// Current y position compared to the center of the screen (the horizon)
		int		y_current_position = y - (vars->screen_height / 2); // int		p = y - screenHeight / 2;

		// Vertical position of the camera.
		// NOTE:
		// with 0.5, it's exactly in the center between floor and ceiling, matching also how the walls are being raycasted.
		// For different values than 0.5, a separate loop must be done for ceiling and floor since they're no longer symmetrical.
		float	vertical_position_camera = 0.5 * vars->screen_height; // float	posZ = 0.5 * screenHeight;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		// NOTE:
		// this is affine texture mapping, which is not perspective correct except for perfectly horizontal and vertical surfaces like the floor.
		// NOTE:
		// this formula is explained as follows:
		// The camera ray goes through the following two points:
		// the camera itself, which is at a certain height (posZ), and a point in front of the camera
		// (through an imagined vertical plane containing the screen pixels)
		// with horizontal distance 1 from the camera, and vertical position p lower than posZ (posZ - p).
		// When going through that point, the line has vertically traveled by p units and horizontally by 1 unit.
		// To hit the floor, it instead needs to travel by posZ units.
		// It will travel the same ratio horizontally.
		// The ratio was 1 / p for going through the camera plane,
		// so to go posZ times farther to reach the floor,
		// we get that the total horizontal distance is posZ / p.
		float	row_distance = vertical_position_camera / y_current_position; // float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float	x_step_floor = row_distance * (x_ray_direction_1 - x_ray_direction_0) / vars->screen_width; // float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		float	y_step_floor = row_distance * (y_ray_direction_1 - y_ray_direction_0) / vars->screen_width; // float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;
		
		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float	x_floor = vars->x_position_vector + row_distance * x_ray_direction_0; // float floorX = posX + rowDistance * rayDirX0;
		float	y_floor = vars->y_position_vector + row_distance * y_ray_direction_0; // float floorY = posY + rowDistance * rayDirY0;
	
		int	x;

		x = 0;
		while (x < vars->screen_width)
		{
			x += 1;
			// the cell coord is simply got from the integer parts of floorX and floorY
			int	x_cell = (int)x_floor; // int cellX = (int)(floorX);
			int y_cell = (int)y_floor; // int cellY = (int)(floorY);
			
			// get the texture coordinate from the fractional part
			// TODO: Change name texWidth
			int x_texture_coordinate = (int)(texWidth * (x_floor - x_cell)) & (texWidth - 1); // int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			// TODO: Change name texHeight
			int y_texture_coordinate = (int)(texHeight * (y_floor - y_cell)) & (texHeight - 1); // int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
			
			x_floor += x_step_floor;
			y_floor += y_step_floor;
			
			// choose texture and draw the pixel
			int	checker_board_pattern = (int)((x_cell + y_cell) & 1); // int	checkerBoardPattern = (int(cellX + cellY)) & 1;
			int	floor_texture; // int	floorTexture;

			if (checker_board_pattern == 0)
			{
				floor_texture = 3;
			}
			else
			{
				floor_texture = 4;
			}
			int	ceiling_texture = 6; // int	ceilingTexture = 6;

			// Uint32 color;
			// 
			// // floor
			// color = texture[floorTexture][texWidth * ty + tx];
			// color = (color >> 1) & 8355711; // make a bit darker
			// buffer[y][x] = color;
			// 
			// //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			// color = texture[ceilingTexture][texWidth * ty + tx];
			// color = (color >> 1) & 8355711; // make a bit darker
			// buffer[screenHeight - y - 1][x] = color;
			unsigned int	color;
			
			// floor
			color = *(vars->texture_list[floor_texture].data.addr + vars->texture_list[floor_texture].height * texture_y + texture_x);
			color = (color >> 1) & 8355711;
			vars->image.addr[y * vars->screen_width + x_axis] = color;

			// ceiling
			color = *(vars->texture_list[ceiling_texture].data.addr + vars->texture_list[ceiling_texture].height * texture_y + texture_x);
			color = (color >> 1) & 8355711;
			vars->image.addr[y * vars->screen_width + x_axis] = color;
		}
	}
#endif // FLOOR_HORIZONTAL
