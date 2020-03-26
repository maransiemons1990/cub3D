/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran          #+#    #+#                */
/*   Updated: 2020/03/26 20:37:27 by Maran         ########   odam.nl         */
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

void			verLine(t_base *base, int x)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
    double	perpWallDist;
	
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
	//   printf("----------------------------------------------\n");
    //choose wall color
    color = 16711680;
    //give x and y sides different brightness
    if (base->game.side == 1) 
	 	color = 16728899;
	//printf(" x =[%d], start=[%d], end=[%d], color=[%d]\n", x, drawStart, drawEnd, color);
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(base, x, drawStart, color);
		drawStart++;
	}
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
		//   printf("Jump in X direction: new mapX[%d], new sideDistX[%f]\n", mapX, sideDistX);
    	}
    	else
    	{
        		base->game.sideDistY += base->game.deltaDistY;
        		base->game.mapY += base->game.stepY;
        		base->game.side = 1;
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
	double planeX;
	double planeY;
	
	planeX = 0;	//the 2d raycaster version of camera plane
	planeY = 0.66;
	//calculate ray position and direction
    cameraX = 2 * x / (double)base->read.render_x - 1; //x-coordinate in camera space
    base->game.rayDirX = base->game.dirX + planeX * cameraX;
    base->game.rayDirY = base->game.dirY + planeY * cameraX;
    //which box of the map we're in
    base->game.mapX = (int)base->read.x_pos;
	base->game.mapY = (int)base->read.y_pos;
	//length of ray from one x or y-side to next x or y-side
    base->game.deltaDistX = fabs(1 / base->game.rayDirX);
    base->game.deltaDistY = fabs(1 / base->game.rayDirY);
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
    	verLine(base, x);
	  	x++;
	}
	base->game.oldtime = base->game.time;
	base->game.time = clock();
	base->game.frametime = (base->game.time - base->game.oldtime) / CLOCKS_PER_SEC;
	base->game.movespeed = base->game.frametime * 5.0;
	base->game.rotspeed = base->game.frametime * 3.0;
	return (0);
}

int				loop(t_base *base)
{
	static int	update = 1;
	//TEST
	// base->mlx.new_img = mlx_new_image(base->mlx.mlx, base->read.render_x, base->read.render_y);
	// base->mlx.new_addr = mlx_get_data_addr(base->mlx.new_img, &base->mlx.bits_per_pixel, &base->mlx.line_length, &base->mlx.endian);
	printf("Hier?\n");
	//
	base->mlx.img = mlx_new_image(base->mlx.mlx, base->read.render_x, base->read.render_y);
	base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bits_per_pixel, &base->mlx.line_length, &base->mlx.endian);
	// base->mlx.img = base->mlx.new_img;
	// base->mlx.addr = base->mlx.new_addr;
	
	
	if (base->game.move_front == 1)
	{
		if (TWOD[base->read.y_pos][(int)(base->read.x_pos + base->game.dirX * base->game.movespeed)] == '+')
			base->read.x_pos += base->game.dirX * base->game.movespeed;
		if (TWOD[(int)(base->read.y_pos + base->game.dirY * base->game.movespeed)][base->read.x_pos] == '+')
			base->read.y_pos += base->game.dirY * base->game.movespeed;
		update = 1;
	}
	if (update)
	{
		raycasting(base);
		mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
		//mlx_destroy_image(base->mlx.mlx, base->mlx.new_img);
	}
	update = 0;
	return (0);
}










		// mlx_clear_window(base->mlx.mlx, base->mlx.mlx_win);
		// // gl->img = mlx_new_image(gl->mlx, gl->s_x, gl->s_y);
		// // gl->disp = mlx_get_data_addr(gl->img, &(gl->bpp), &(gl->sizeline),
		// // 	&(gl->endian));