/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/08 10:58:18 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <string.h>

/*
** Pushing pixels to the window. we will have to buffer all of our pixels to a image
** which we will then push to the window.
** Instead of push the pixel instantly to the window (without waiting for the frame to be entirely rendered).
*/

void            my_mlx_pixel_put(t_base *base, int x, int y, int color)
{
    char    *dst;

    dst = base->mlx.addr + (y * base->mlx.line_length + x * (base->mlx.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void			verLine2(t_base *base, int x)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
    double	perpWallDist;
	char	*dest;

	double	wallX; //where exactly the wall was hit
	int 	texX;
	double	step;
	double	texPos;
	int		y;
	int		texY;
	int		color;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (base->game.side == 0)
		perpWallDist = (base->game.mapX - base->read.x_pos + (1 - base->game.stepX) / 2) / base->game.rayDirX;
	else
		perpWallDist = (base->game.mapY - base->read.y_pos + (1 - base->game.stepY) / 2) / base->game.rayDirY;
	//Calculate height of line to draw on screen
   	lineHeight = (int)(base->read.render_y / perpWallDist);
   	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + base->read.render_y / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + base->read.render_y / 2;
	if(drawEnd >= base->read.render_y)
		drawEnd = base->read.render_y - 1;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
  	
	//calculate value of wallX (The value wallX represents the exact value where the wall was hit)
    if (base->game.side == 0)
 	 	wallX = base->read.y_pos + perpWallDist * base->game.rayDirY;	//the exact x or y coordinate in the world,
    else
		wallX = base->read.x_pos + perpWallDist * base->game.rayDirX;
    wallX -= (int)wallX; 												//substracting the integer value of the wall off it
	//x coordinate on the texture
    texX = wallX * (double)base->game.texWidth; //(int)WallX !!!! Hierna een texture!
    if (base->game.side == 0 && base->game.rayDirX > 0)
		texX = base->game.texWidth - texX - 1;
    if (base->game.side == 1 && base->game.rayDirY < 0)
		texX = base->game.texWidth - texX - 1;
	//Now that we know the x-coordinate of the texture, we know that this coordinate will remain the same,
	// because we stay in the same vertical stripe of the screen.
	
	// The step size tells how much to increase in the texture coordinates (in floating point) for every pixel in vertical screen coordinates.
	// It then needs to cast the floating point value to integer to select the actual texture pixel.
	// = affine texture mapping
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * base->game.texHeight / lineHeight;
   
    // Starting texture coordinate
    texPos = (drawStart - base->read.render_y / 2 + lineHeight / 2) * step;
    y = drawStart;
	//printf("--------------------- x = [%d]---------------------\n", base->game.count);
	while (y < drawEnd)
    {
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        texY = (int)texPos & (base->game.texHeight - 1);
        texPos += step;
		//-------------NEW--------------
		if (base->game.tex_side == 1)
		{
			dest = base->tex_no.png_addr + (texY * base->tex_no.png_line_length + texX * (base->tex_no.png_bits_per_pixel / 8));
			color = *(unsigned int*)dest;
		}
		else if (base->game.tex_side == 2) //
		{
			dest = base->tex_ea.png_addr + (texY * base->tex_ea.png_line_length + texX * (base->tex_ea.png_bits_per_pixel / 8));
			color = *(unsigned int*)dest;
		}
		else if (base->game.tex_side == 3)
		{
			dest = base->tex_so.png_addr + (texY * base->tex_so.png_line_length + texX * (base->tex_so.png_bits_per_pixel / 8));
			color = *(unsigned int*)dest;
		}
		else //W
		{
			dest = base->tex_we.png_addr + (texY * base->tex_we.png_line_length + texX * (base->tex_we.png_bits_per_pixel / 8));
			color = *(unsigned int*)dest;
		}
		
		//-----------------------------
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        // if(side == 1) color = (color >> 1) & 8355711;
        //buffer[y][x] = color;
		my_mlx_pixel_put(base, x, y, color);
		y++;
      }
	  base->game.count++;
}

void	DDA(t_base *base)
{
	//perform DDA
    int hit;
	
	hit = 0;	//was there a wall hit?
 	//printf("START pos [%d][%d] = [%c]\n", base->read.y_pos, base->read.x_pos, base->read.array[mapY][mapX]);
   	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		//printf("TWOD[%d][%d] = [%c]\n", mapY, mapX, base->read.array[mapY][mapX]);
    	if(base->game.sideDistX < base->game.sideDistY)
    	{
    		base->game.sideDistX += base->game.deltaDistX;
    		base->game.mapX += base->game.stepX;
    		base->game.side = 0;
			base->game.tex_side = base->game.stepX < 0 ? 2 : 4;
		//   printf("Jump in X direction: new mapX[%d], new sideDistX[%f]\n", mapX, sideDistX);
    	}
    	else
    	{
        		base->game.sideDistY += base->game.deltaDistY;
        		base->game.mapY += base->game.stepY;
        		base->game.side = 1;
				base->game.tex_side = base->game.stepY < 0 ? 3 : 1;
		//   printf("Jump in Y direction: new mapY[%d], new sideDistY[%f]\n", mapY, sideDistY);
    	}
    	//Check if ray has hit a wall
		//printf("CHANGED TWOD[%d][%d] = [%c][%d]\n", mapY, mapX, base->read.array[mapY][mapX], base->read.array[mapY][mapX]);
    	if(TWOD[base->game.mapY][base->game.mapX] > 0 && TWOD[base->game.mapY][base->game.mapX] != '+')
		{
			hit = 1;
			//	printf("**HIT**[%d][%d]\n", mapY, mapX);
		}
	}
}

void	initial_step_sidedist(t_base *base)
{
	//calculate step and initial sideDist
    if(base->game.rayDirX < 0)
    {
    	base->game.stepX = -1;
    	base->game.sideDistX = (base->read.x_pos - base->game.mapX) * base->game.deltaDistX;
    }
    else
    {
    	base->game.stepX = 1;
    	base->game.sideDistX = (base->game.mapX + 1.0 - base->read.x_pos) * base->game.deltaDistX;
    }
    if(base->game.rayDirY < 0)
    {
      base->game.stepY = -1;
      base->game.sideDistY = (base->read.y_pos - base->game.mapY) * base->game.deltaDistY;
    }
    else
    {
    	base->game.stepY = 1;
    	base->game.sideDistY = (base->game.mapY + 1.0 - base->read.y_pos) * base->game.deltaDistY;
    }
}
void	ray_position(t_base *base, int x)
{
	double cameraX;

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
	//calculate ray position and direction
    if (base->read.pos == 'W' || base->read.pos == 'S')		//Spiegelen terug gedraaid, maar nu kleuren verkeerd om?
		cameraX = (2 * x / (double)base->read.render_x - 1) * -1; //x-coordinate in camera space
    else
		cameraX = 2 * x / (double)base->read.render_x - 1;
	base->game.rayDirX = base->game.dirX + base->game.planeX * cameraX;
    base->game.rayDirY = base->game.dirY + base->game.planeY * cameraX;
    //which box of the map we're in
    base->game.mapX = (int)base->read.x_pos;
	base->game.mapY = (int)base->read.y_pos;
	//length of ray from one x or y-side to next x or y-side
    base->game.deltaDistX = fabs(1 / base->game.rayDirX);
    base->game.deltaDistY = fabs(1 / base->game.rayDirY);
	//printf("ROTATE raypostion dirX[%f], dirY[%f], planeX[%f], planeY[%f]\n", base->game.dirX, base->game.dirY, base->game.planeX, base->game.planeY);
}

int		raycasting(t_base *base)
{
	int x;

	x = 0;
	while(x < base->read.render_x)
	{
		ray_position(base, x);
		initial_step_sidedist(base);
		DDA(base);
    	//draw the pixels of the stripe as a vertical line //and calculate first
    	//verLine(base, x);
		verLine2(base, x);
	  	x++;
	}
	base->game.oldtime = base->game.time;
	base->game.time = clock();
	base->game.frametime = (base->game.time - base->game.oldtime) / CLOCKS_PER_SEC;
	base->game.movespeed = base->game.frametime * 5.0; //werkt nog niet lekker.
	base->game.rotspeed = base->game.frametime * 3.0;
	return (0);
}

void			rotate(t_base *base)
{
	double	oldDirX;
	double	oldPlaneX;
	
	if (base->game.rotate_right == 1)
	{
		//printf("ROTATE LEFT rotspeed[%f]", base->game.rotspeed);
		oldDirX = base->game.dirX;
		base->game.dirX = base->game.dirX * cos(base->game.rotspeed) - base->game.dirY * sin(base->game.rotspeed);
		base->game.dirY = oldDirX * sin(base->game.rotspeed) + base->game.dirY * cos(base->game.rotspeed);
		oldPlaneX = base->game.planeX;
		base->game.planeX = base->game.planeX * cos(base->game.rotspeed) - base->game.planeY * sin(base->game.rotspeed);
		base->game.planeY = oldPlaneX * sin(base->game.rotspeed) + base->game.planeY * cos(base->game.rotspeed);
		printf("ROTATE RIGHT dirX[%f], dirY[%f], planeX[%f], planeY[%f]\n", base->game.dirX, base->game.dirY, base->game.planeX, base->game.planeY);
	}
	if (base->game.rotate_left == 1)
	{
		oldDirX = base->game.dirX;
		base->game.dirX = base->game.dirX * cos(-base->game.rotspeed) - base->game.dirY * sin(-base->game.rotspeed);
		base->game.dirY = oldDirX * sin(-base->game.rotspeed) + base->game.dirY * cos(-base->game.rotspeed);
		oldPlaneX = base->game.planeX;
		base->game.planeX = base->game.planeX * cos(-base->game.rotspeed) - base->game.planeY * sin(-base->game.rotspeed);
		base->game.planeY = oldPlaneX * sin(-base->game.rotspeed) + base->game.planeY * cos(-base->game.rotspeed);
		printf("ROTATE LEFT dirX[%f], dirY[%f], planeX[%f], planeY[%f]\n", base->game.dirX, base->game.dirY, base->game.planeX, base->game.planeY);
	}
}


//* base->game.movespeed; Overal uitgehaald. Want issues.
void			move(t_base *base)
{
	if (base->game.move_front == 1)
	{
		if (TWOD[base->read.y_pos][(int)(base->read.x_pos + base->game.dirX)] == '+')
			base->read.x_pos += base->game.dirX;		//EW
		if (TWOD[(int)(base->read.y_pos + base->game.dirY)][base->read.x_pos] == '+')
			base->read.y_pos += base->game.dirY;		//SN
		printf("FRONT [%d][%d]\n", base->read.y_pos, base->read.x_pos);
	}
	if (base->game.move_back == 1)
	{
		if (TWOD[base->read.y_pos][(int)(base->read.x_pos - base->game.dirX)] == '+')
			base->read.x_pos -= base->game.dirX;
		if (TWOD[(int)(base->read.y_pos - base->game.dirY)][base->read.x_pos] == '+')
			base->read.y_pos -= base->game.dirY;
		printf("BACK [%d][%d]\n", base->read.y_pos, base->read.x_pos);
	}
	if (base->game.move_right == 1)
	{
		if (TWOD[base->read.y_pos][(int)(base->read.x_pos - base->game.dirY)] == '+')
		 	base->read.x_pos -= base->game.dirY;		//S N
		if (TWOD[(int)(base->read.y_pos + base->game.dirX)][base->read.x_pos] == '+')
			base->read.y_pos += base->game.dirX;		//E W
		printf("RIGHT [%d][%d]\n", base->read.y_pos, base->read.x_pos);
	}
	if (base->game.move_left == 1)
	{
		if (TWOD[base->read.y_pos][(int)(base->read.x_pos + base->game.dirY)] == '+')
			base->read.x_pos += base->game.dirY;	//S N
		if (TWOD[(int)(base->read.y_pos - base->game.dirX)][base->read.x_pos] == '+')
			base->read.y_pos -= base->game.dirX;	//E W
		printf("LEFT [%d][%d]\n", base->read.y_pos, base->read.x_pos);
	}
	if (base->game.rotate_left == 1 || base->game.rotate_right == 1)
		rotate(base);
}

/*
** 
** img_ptr - specifies the image to use. 
** bits_per_pixel - the number of bits needed to represent a pixel color
** (also called the depth of the image).
** size_line - the number of bytes used to store one line of the image in memory.
** This information is needed to move from one line to another in the image.
** endian - tells you wether the pixel color in the image needs to be stored in
** little endian (== 0), or big endian (== 1).
*/


int				loop(t_base *base)
{
	base->mlx.img = mlx_new_image(base->mlx.mlx, base->read.render_x, base->read.render_y);
	base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bits_per_pixel, &base->mlx.line_length, &base->mlx.endian);
	if (base->game.update)
		move(base);
	raycasting(base);
	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
	//mlx_destroy_image(base->mlx.mlx, base->mlx.new_img);
	base->game.update = 0;
	return (0);
}
