/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran          #+#    #+#                */
/*   Updated: 2020/03/25 19:12:13 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <string.h>
//#include <vector.h>
//#include <iostream>

//#include "quickcg.h"


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

void		verLine(t_base *base, int x, int drawStart, int drawEnd, int color)
{
	//printf(" x =[%d], start=[%d], end=[%d], color=[%d]\n", x, drawStart, drawEnd, color);
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(base, x, drawStart, color);
		drawStart++;
	}
}

void	orientation(t_base *base, double *dirX, double *dirY)
{
	if (base->read.pos == 'N')
		*dirY = -1;
	if (base->read.pos == 'S')
		*dirY = 1;
	if (base->read.pos == 'E')
		*dirX = 1;	
	if (base->read.pos == 'W')
		*dirX = -1;
}

int		raycasting(t_base *base)
{
	//double posX = 22, posY = 12;  //x and y start position
	double dirX = 0, dirY = 0; //initial direction vector
	orientation(base, &dirX, &dirY);
	//printf("orientation dirY = [%f], dirY = [%f]\n", dirX, dirY);
	
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
	// double frameTime;
	int x = 0;
	
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;

	while(x < base->read.render_x)
	{
		//calculate ray position and direction
     	double cameraX = 2 * x / (double)base->read.render_x - 1; //x-coordinate in camera space
    	double rayDirX = dirX + planeX * cameraX;
    	double rayDirY = dirY + planeY * cameraX;
      	//which box of the map we're in
      	int mapX = (int)base->read.x_pos;
		int mapY = (int)base->read.y_pos;

	    //length of ray from current position to next x or y-side
    	double sideDistX;
      	double sideDistY;

		//length of ray from one x or y-side to next x or y-side
      	double deltaDistX = fabs(1 / rayDirX);
     	double deltaDistY = fabs(1 / rayDirY);
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
        	sideDistX = (base->read.x_pos - mapX) * deltaDistX;
      	}
      	else
      	{
        	stepX = 1;
        	sideDistX = (mapX + 1.0 - base->read.x_pos) * deltaDistX;
     	}
      	if(rayDirY < 0)
      	{
      	  stepY = -1;
      	  sideDistY = (base->read.y_pos - mapY) * deltaDistY;
      	}
      	else
     	{
        	stepY = 1;
        	sideDistY = (mapY + 1.0 - base->read.y_pos) * deltaDistY;
     	}
      	//perform DDA
	  	//printf("START pos [%d][%d] = [%c]\n", base->read.y_pos, base->read.x_pos, base->read.array[mapY][mapX]);
      	while (hit == 0)
      	{
        //jump to next map square, OR in x-direction, OR in y-direction
		//printf("TWOD[%d][%d] = [%c]\n", mapY, mapX, base->read.array[mapY][mapX]);
        	if(sideDistX < sideDistY)
        	{
        		sideDistX += deltaDistX;
        		mapX += stepX;
        		side = 0;
			//   printf("Jump in X direction: new mapX[%d], new sideDistX[%f]\n", mapX, sideDistX);
        	}
        	else
        	{
         		sideDistY += deltaDistY;
         		mapY += stepY;
         		side = 1;
			//   printf("Jump in Y direction: new mapY[%d], new sideDistY[%f]\n", mapY, sideDistY);
        	}
        	//Check if ray has hit a wall
			//printf("CHANGED TWOD[%d][%d] = [%c][%d]\n", mapY, mapX, base->read.array[mapY][mapX], base->read.array[mapY][mapX]);
        	if(TWOD[mapY][mapX] > 0 && TWOD[mapY][mapX] != '+')
			{
				hit = 1;
			//	printf("**HIT**[%d][%d]\n", mapY, mapX);
			}
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    	if (side == 0)
			perpWallDist = (mapX - base->read.x_pos + (1 - stepX) / 2) / rayDirX;
    	else
			perpWallDist = (mapY - base->read.y_pos + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
    	lineHeight = (int)(base->read.render_y / perpWallDist);

    	//calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + base->read.render_y / 2;
		if(drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + base->read.render_y / 2;
		if(drawEnd >= base->read.render_y)
			drawEnd = base->read.render_y - 1;

		//   printf("----------------------------------------------\n");
    	//choose wall color
    	color = 16711680;
    	//give x and y sides different brightness
    	if (side == 1) 
		 	color = 16728899;
    	//draw the pixels of the stripe as a vertical line
    	verLine(base, x, drawStart, drawEnd, color);
	  	x++;
	}
    //timing for input and FPS counter
    // oldTime = time;
    // time = GetTickCount();
    // frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
   // print(1.0 / frameTime); //FPS counter
    //redraw();
    //cls();

	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
	
    // //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    // readKeys();
    // //move forward if no wall in front of you
    // if(keyDown(SDLK_UP))
    // {
    //   if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if(keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //   if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    // }
    // //rotate to the right
    // if(keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if(keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	// }
	return (0);
}