/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/14 17:22:11 by Maran         ########   odam.nl         */
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

/*
** Reversed my_mlx_pixel_put-dest formula.
** We got the addr of the texture. So we can get the pixel color of a certain
** texturecoordinate. Coordinate color = addr + coordinate.
*/

int				texture_pick_wallside(t_base *base, int texX, int texY)
{
	char	*dest;
	int		color;
	
	if (base->game.tex_side == 1)
	{
		dest = base->tex_no.png_addr + (texY * base->tex_no.png_line_length + texX * (base->tex_no.png_bits_per_pixel / 8));
		color = *(unsigned int*)dest;
	}
	else if (base->game.tex_side == 2)
	{
		dest = base->tex_ea.png_addr + (texY * base->tex_ea.png_line_length + texX * (base->tex_ea.png_bits_per_pixel / 8));
		color = *(unsigned int*)dest;
		color = (color >> 1) & 8355711;
	}
	else if (base->game.tex_side == 3)
	{
		dest = base->tex_so.png_addr + (texY * base->tex_so.png_line_length + texX * (base->tex_so.png_bits_per_pixel / 8));
		color = *(unsigned int*)dest;
	}
	else
	{
		dest = base->tex_we.png_addr + (texY * base->tex_we.png_line_length + texX * (base->tex_we.png_bits_per_pixel / 8));
		color = *(unsigned int*)dest;
		color = (color >> 1) & 8355711;
	
	}
	return (color);
}

/*
** PERPWALLDIST: Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
** LINEHIGHT: Calculate height of line to draw on screen
** DRAWSTART/END: calculate lowest and highest pixel to fill in current stripe
** ------------Textured wall------------------------------------------
** WALLX: calculate value of wallX (The value wallX represents the exact value where the wall was hit)
** the exact x or y coordinate in the world.
** Next substracting the integer value of the wall off it.
*/

void			draw_calculations_wall(t_base *base)
{
    if (base->game.side == 0)
		base->wall.perpWallDist = (base->game.mapX - base->read.x_pos + (1 - base->game.stepX) / 2) / base->game.rayDirX;
	else
		base->wall.perpWallDist = (base->game.mapY - base->read.y_pos + (1 - base->game.stepY) / 2) / base->game.rayDirY;
   	base->wall.lineHeight = (int)(base->read.render_y / base->wall.perpWallDist);
	base->wall.drawStart = -base->wall.lineHeight / 2 + base->read.render_y / 2;
	if(base->wall.drawStart < 0)
		base->wall.drawStart = 0;
	base->wall.drawEnd = base->wall.lineHeight / 2 + base->read.render_y / 2;
	if(base->wall.drawEnd >= base->read.render_y)
		base->wall.drawEnd = base->read.render_y - 1;
    if (base->game.side == 0)
 	 	base->wall.wallX = base->read.y_pos + base->wall.perpWallDist * base->game.rayDirY;
    else
		base->wall.wallX = base->read.x_pos + base->wall.perpWallDist * base->game.rayDirX;
    base->wall.wallX -= (int)base->wall.wallX;
}

/*
** TEXX: x coordinate on the texture
** This coordinate will remain the same, because we stay in the same vertical stripe of the screen.
** STEP: How much to increase the texture coordinate (in floating point) per screen pixel, 
** every pixel in vertical screen coordinates.
** It then needs to cast the floating point value to integer to select the actual texture pixel.
** = affine texture mapping
** TEXPOS: Starting texture coordinate.
*/

void			texture_coordinates_wall(t_base *base)
{
	base->tex_co.texX = base->wall.wallX * (double)base->game.texWidth; //(int)WallX !!!! Hierna een texture!
    if (base->game.side == 0 && base->game.rayDirX > 0)
		base->tex_co.texX = base->game.texWidth - base->tex_co.texX - 1;
    if (base->game.side == 1 && base->game.rayDirY < 0)
		base->tex_co.texX = base->game.texWidth - base->tex_co.texX - 1;
	base->tex_co.step = 1.0 * base->game.texHeight / base->wall.lineHeight;
    base->tex_co.texPos = (base->wall.drawStart - base->read.render_y / 2 + base->wall.lineHeight / 2) * base->tex_co.step;
}

/*
** TEXY: Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow. 
** TEXPOS: Starting texture coordinate change with a step.
** ----OWN PART----
** Check which side the ray the wall hit (1[N], E[2], S[3], W[4])
** This determines which texture is used as color.
** E and W walls have a slightly darker color (shadow): R, G and B byte each
** divided through two with a "shift" and an "and"
** my_mlx: set wall coordinate to new color.
*/

void			verLine(t_base *base, int x)
{
	int		texY;
	int		color;
	int		y;

	draw_calculations_wall(base);
	texture_coordinates_wall(base);
    y = base->wall.drawStart;
	while (y < base->wall.drawEnd)
    {
        texY = (int)base->tex_co.texPos & (base->game.texHeight - 1);
        base->tex_co.texPos += base->tex_co.step;
		color = texture_pick_wallside(base, base->tex_co.texX, texY);
		my_mlx_pixel_put(base, x, y, color);
		y++;
    }
}

/*
** perform DDA
** HIT: was there a wall hit?
** jump to next map square, OR in x-direction, OR in y-direction.
** if: Jump in X direction.
** else: JUmp in Y direction.
** Check if ray has hit a wall
*/

void			DDA(t_base *base)
{
    int		hit;
	
	hit = 0;
   	while (hit == 0)
	{
    	if (base->game.sideDistX < base->game.sideDistY)
    	{
    		base->game.sideDistX += base->game.deltaDistX;
    		base->game.mapX += base->game.stepX;
    		base->game.side = 0;
			base->game.tex_side = base->game.stepX < 0 ? 2 : 4;
    	}
    	else
    	{
        	base->game.sideDistY += base->game.deltaDistY;
        	base->game.mapY += base->game.stepY;
        	base->game.side = 1;
			base->game.tex_side = base->game.stepY < 0 ? 3 : 1;
    	}
    	if (TWOD[base->game.mapY][base->game.mapX] > 0 && TWOD[base->game.mapY][base->game.mapX] != '+')
			hit = 1;
	}
}

/*
** Calculate step and initial sideDist
*/

void			initial_step_sidedist(t_base *base)
{
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

/*
** -PLANE: the 2d raycaster version of camera plane
** if (base->game.dirY == 0) THEN planeX = 0, planeY 0.66 --> N and S
** if (base->game.dirY == 1 || == -1) THEN planeX = 0.66 , planeY 0 --> E and W
** -CAMERAX: x-coordinate in camera space
** if W || S the image was mirrored. Unmirror: camerax * -1.
** -RAYDIR: calculate ray position and direction
** -MAPX/Y: which box of the map we're in
** -DELTADIST: length of ray from one x or y-side to next x or y-side
*/

void			ray_position(t_base *base, int x)
{
	double	cameraX;
	
	base->game.planeX = (base->game.dirY == 0) ? 0 : 0.66;
	base->game.planeY = (base->game.dirY == 0) ? 0.66 : 0;
    if (base->read.pos == 'W' || base->read.pos == 'S')
		cameraX = (2 * x / (double)base->read.render_x - 1) * -1;
    else
		cameraX = 2 * x / (double)base->read.render_x - 1;
	base->game.rayDirX = base->game.dirX + base->game.planeX * cameraX;
    base->game.rayDirY = base->game.dirY + base->game.planeY * cameraX;
    base->game.mapX = (int)base->read.x_pos;
	base->game.mapY = (int)base->read.y_pos;
    base->game.deltaDistX = fabs(1 / base->game.rayDirX);
    base->game.deltaDistY = fabs(1 / base->game.rayDirY);
}

int				raycasting(t_base *base)
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
		zbuffer(base, x);
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
	floor_ceiling_smooth(base);
	//floor_ceiling_texture(base);
	raycasting(base);
	//printf("nb_sprites = %d\n", base->read.nb_sprites);
	//sprite(base);
	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
	//mlx_destroy_image(base->mlx.mlx, base->mlx.new_img);
	base->game.update = 0;
	return (0);
}
