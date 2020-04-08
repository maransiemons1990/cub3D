/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 14:53:21 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/08 19:05:30 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floorcasting(t_base *base)
{
	int y;
	int x;
	int color;

	y = base->read.render_y / 2 + 1;
	while(y < base->read.render_y)
    {
		x = 0;
		while(x < base->read.render_x)
      	{
			color = base->read.f_color;
        	color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(base, x, y, color);
        	color = base->read.c_color;
        	color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(base, x, (base->read.render_y - y - 1), color);
			x++;
      	}
	  y++;
    }
}


void	floorcasting_texture(t_base *base)
{
	int y;
	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;
	int p;
	float posZ;
	float rowDistance;
	float floorStepX;
	float floorStepY;
	float floorX;
	float floorY;

	y = base->read.render_y / 2 + 1;
	//dubbel
	if (base->game.dirY == 0) //NS
	{
		base->game.planeX = 0;	//the 2d raycaster version of camera plane
		base->game.planeY = 0.66;	
	}
	else					//EW
	{
		base->game.planeX = 0.66;
		base->game.planeY = 0;	
	}
	//Einde dubbel
	while(y < base->read.render_y)
    {
		//rayDir for leftmost ray (x = 0) and rightmost ray (x = width screen)
      	rayDirX0 = base->game.dirX - base->game.planeX; //W dirX=-1 dirY=0/ -1 - 0.66= -1.66
      	rayDirY0 = base->game.dirY - base->game.planeY; // 				/ 0 - 0 = 0
      	rayDirX1 = base->game.dirX + base->game.planeX; //				/ -1 + 0.66 = 0.44
      	rayDirY1 = base->game.dirY + base->game.planeY; //				/ 0 + 0 = 0	

      	//Current y position compared to the center of the screen (the horizon)
      	p = y - base->read.render_y / 2;

      	// Vertical position of the camera.
      	// NOTE: with 0.5, it's exactly in the center between floor and ceiling,
      	// matching also how the walls are being raycasted. For different values
      	// than 0.5, a separate loop must be done for ceiling and floor since
      	// they're no longer symmetrical.
      	posZ = 0.5 * base->read.render_y;

      	// Horizontal distance from the camera to the floor for the current row.
      	// 0.5 is the z position exactly in the middle between floor and ceiling.
      	// NOTE: this is affine texture mapping, which is not perspective correct
      	// except for perfectly horizontal and vertical surfaces like the floor.
      	// NOTE: this formula is explained as follows: The camera ray goes through
      	// the following two points: the camera itself, which is at a certain
      	// height (posZ), and a point in front of the camera (through an imagined
      	// vertical plane containing the screen pixels) with horizontal distance
      	// 1 from the camera, and vertical position p lower than posZ (posZ - p). When going
      	// through that point, the line has vertically traveled by p units and
      	// horizontally by 1 unit. To hit the floor, it instead needs to travel by
      	// posZ units. It will travel the same ratio horizontally. The ratio was
      	// 1 / p for going through the camera plane, so to go posZ times farther
      	// to reach the floor, we get that the total horizontal distance is posZ / p.
      	rowDistance = posZ / p;

      	// calculate the real world step vector we have to add for each x (parallel to camera plane)
      	// adding step by step avoids multiplications with a weight in the inner loop
      	floorStepX = rowDistance * (rayDirX1 - rayDirX0) / base->read.render_y;
      	floorStepY = rowDistance * (rayDirY1 - rayDirY0) / base->read.render_y;

      	// real world coordinates of the leftmost column. This will be updated as we step to the right.
      	floorX = base->read.x_pos + rowDistance * rayDirX0;
      	floorY = base->read.y_pos + rowDistance * rayDirY0;

		int x;
		int color;
		int cellX;
		int cellY;
	
		char		*dest;
		x = 0;
		while (x < base->read.render_x)
      	{
			// the cell coord is simply got from the integer parts of floorX and floorY
        	cellX = (int)(floorX);
        	cellY = (int)(floorY);

        	// get the texture coordinate from the fractional part
        	int tx = (int)(base->game.texWidth * (floorX - cellX)) & (base->game.texWidth - 1);
        	int ty = (int)(base->game.texHeight * (floorY - cellY)) & (base->game.texHeight - 1);

        	floorX += floorStepX;
        	floorY += floorStepY;
			
			//NEW
			//dest = base->tex_f.png_addr + (base->game.texWidth * ty + tx * (base->tex_we.png_bits_per_pixel / 8)); MINDER MOOI
			dest = base->tex_f.png_addr + (base->tex_f.png_line_length * ty + tx * (base->tex_we.png_bits_per_pixel / 8));
			color = *(unsigned int*)dest;
			color = (color >> 1) & 8355711;
			my_mlx_pixel_put(base, x, y, color);
		
        	//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        	//dest = base->tex_c.png_addr + (base->game.texWidth * ty + tx * (base->tex_we.png_bits_per_pixel / 8)); MINDER MOOI
			dest = base->tex_c.png_addr + (base->tex_f.png_line_length * ty + tx * (base->tex_we.png_bits_per_pixel / 8));
			color = *(unsigned int*)dest;
			color = (color >> 1) & 8355711;
			my_mlx_pixel_put(base, x, (base->read.render_y - y - 1), color);
			x++;
      	}
	  y++;
    }
}
