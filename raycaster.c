/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/06 11:27:01 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <string.h>

/*
** Pushing pixels to the window. we will have to buffer all of our pixels to a image
** which we will then push to the window.
** Instead of push the pixel instantly to the window (without waiting for the frame to be entirely rendered).
** Locate postion of pixel: (y * size_line + x * (bits_per_pixel / 8));
** Here we multiply size_line by y as we need to skip y lines (line size does not equal the amount of pixels in a line).
** We then add the remaining x units multiplied by bits_per_pixl / 8 to align with the final location.
*/

void            my_mlx_pixel_put(t_base *base, int x, int y, int color)
{
    char    *dst;

    dst = base->mlx.addr + (y * base->mlx.line_length + x * (base->mlx.bpp / 8));
    *(unsigned int*)dst = color;
}

/*
** Reversed my_mlx_pixel_put-dest formula.
** We got the addr of the texture. So we can get the pixel color of a certain
** texturecoordinate. Coordinate color = addr + coordinate.
** tex[i] --> no 0, ea 1, so 2, we 3,
*/

int				texture_pick_wallside(t_base *base, int texx, int texy)
{
	char	*dest;
	int		color;
	
	if (base->game.tex_side == 1)
	{
		dest = base->tex[0].xpm_addr + (texy * base->tex[0].xpm_line_length + texx * (base->tex[0].xpm_bpp / 8));
		color = *(unsigned int*)dest;
	}
	else if (base->game.tex_side == 2)
	{
		dest = base->tex[1].xpm_addr + (texy * base->tex[1].xpm_line_length + texx * (base->tex[1].xpm_bpp / 8));
		color = *(unsigned int*)dest;
		color = (color >> 1) & 8355711;
	}
	else if (base->game.tex_side == 3)
	{
		dest = base->tex[2].xpm_addr + (texy * base->tex[2].xpm_line_length + texx * (base->tex[2].xpm_bpp / 8));
		color = *(unsigned int*)dest;
	}
	else
	{
		dest = base->tex[3].xpm_addr + (texy * base->tex[3].xpm_line_length + texx * (base->tex[3].xpm_bpp / 8));
		color = *(unsigned int*)dest;
		color = (color >> 1) & 8355711;
	
	}
	return (color);
}

/*
** PERPwALLdIST: Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
** Perpwallshoudn't be smaller then 1 otherwise you can look through the wall. So 1 is the smallest, then lineheight == total rendery.
** LINEHIGHT: Calculate height of line to draw on screen
** DRAWsTART/END: calculate lowest and highest pixel to fill in current stripe
** ------------Textured wall------------------------------------------
** WALLx: calculate value of wallx (The value wallx represents the exact value where the wall was hit)
** the exact x or y coordinate in the world.
** Next substracting the integer value of the wall off it.
*/

void			draw_calculations_wall(t_base *base)
{
    if (base->game.side == 0)
		base->wall.perpwalldist = (base->game.mapx - base->read.x_pos + (1 - base->game.stepx) / 2) / base->game.raydirx;
	else
		base->wall.perpwalldist = (base->game.mapy - base->read.y_pos + (1 - base->game.stepy) / 2) / base->game.raydiry;
	base->wall.perpwalldist = (base->wall.perpwalldist < 1) ? 1 : base->wall.perpwalldist;
	base->wall.lineheight = (int)(base->read.render_y / base->wall.perpwalldist);
	base->wall.drawstart = -base->wall.lineheight / 2 + base->read.render_y / 2;
	if(base->wall.drawstart < 0)
		base->wall.drawstart = 0;
	base->wall.drawend = base->wall.lineheight / 2 + base->read.render_y / 2;
	if(base->wall.drawend >= base->read.render_y)
		base->wall.drawend = base->read.render_y - 1;
    if (base->game.side == 0)
 	 	base->wall.wallx = base->read.y_pos + base->wall.perpwalldist * base->game.raydiry;
    else
		base->wall.wallx = base->read.x_pos + base->wall.perpwalldist * base->game.raydirx;
    base->wall.wallx -= (int)base->wall.wallx;
}

/*
** TEXx: x coordinate on the texture
** This coordinate will remain the same, because we stay in the same vertical stripe of the screen.
** STEP: How much to increase the texture coordinate (in floating point) per screen pixel, 
** every pixel in vertical screen coordinates.
** It then needs to cast the floating point value to integer to select the actual texture pixel.
** = affine texture mapping
** TEXpOS: Starting texture coordinate.
*/

void			texture_coordinates_wall(t_base *base)
{
	base->tex_co.texx = base->wall.wallx * (double)base->game.texwidth; //(int)Wallx !!!! Hierna een texture!
    if (base->game.side == 0 && base->game.raydirx > 0)
		base->tex_co.texx = base->game.texwidth - base->tex_co.texx - 1;
    if (base->game.side == 1 && base->game.raydiry < 0)
		base->tex_co.texx = base->game.texwidth - base->tex_co.texx - 1;
	base->tex_co.step = 1.0 * base->game.texheight / base->wall.lineheight;
    base->tex_co.texpos = (base->wall.drawstart - base->read.render_y / 2 + base->wall.lineheight / 2) * base->tex_co.step;
}

/*
** TEXy: Cast the texture coordinate to integer, and mask with (texheight - 1) in case of overflow. 
** TEXpOS: Starting texture coordinate change with a step.
** ----OWN PART----
** Check which side the ray the wall hit (1[N], E[2], S[3], W[4])
** This determines which texture is used as color.
** E and W walls have a slightly darker color (shadow): R, G and B byte each
** divided through two with a "shift" and an "and"
** my_mlx: set wall coordinate to new color.
*/

void			verLine(t_base *base, int x)
{
	int		texy;
	int		color;
	int		y;

	draw_calculations_wall(base);
	texture_coordinates_wall(base);
    y = base->wall.drawstart;
	while (y < base->wall.drawend)
    {
        texy = (int)base->tex_co.texpos & (base->game.texheight - 1);
        base->tex_co.texpos += base->tex_co.step;
		color = texture_pick_wallside(base, base->tex_co.texx, texy);
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
    	if (base->game.sidedistx < base->game.sidedisty)
    	{
    		base->game.sidedistx += base->game.deltadistx;
    		base->game.mapx += base->game.stepx;
    		base->game.side = 0;
			base->game.tex_side = base->game.stepx < 0 ? 2 : 4;
    	}
    	else
    	{
        	base->game.sidedisty += base->game.deltadisty;
        	base->game.mapy += base->game.stepy;
        	base->game.side = 1;
			base->game.tex_side = base->game.stepy < 0 ? 3 : 1;
    	}
		if (TWOD[base->game.mapy][base->game.mapx] == '1')
			hit = 1;
	}
}

/*
** Calculate step and initial sideDist
*/

void			initial_step_sidedist(t_base *base)
{
    if(base->game.raydirx < 0)
    {
    	base->game.stepx = -1;
    	base->game.sidedistx = (base->read.x_pos - base->game.mapx) * base->game.deltadistx;
    }
    else
    {
		base->game.stepx = 1;
    	base->game.sidedistx = (base->game.mapx + 1.0 - base->read.x_pos) * base->game.deltadistx;
    }
    if(base->game.raydiry < 0)
    {
		base->game.stepy = -1;
		base->game.sidedisty = (base->read.y_pos - base->game.mapy) * base->game.deltadisty;
    }
    else
    {
    	base->game.stepy = 1;
    	base->game.sidedisty = (base->game.mapy + 1.0 - base->read.y_pos) * base->game.deltadisty;
    }
}

/*
** -PLANE: the 2d raycaster version of camera plane
** if (base->game.diry == 0) THEN planex = 0, planey 0.66 -y> N and S
** if (base->game.diry == 1 || == -1) THEN planex = 0.66 , ylaneY 0 --> E and W
** -CAMERAX: x-coordinate in camera space
** if W || S the image was mirrored. Unmirror: camerax * -1.
** -RAYDIR: calculate ray position and direction
** -MAPx/Y: which box of the map we're in
** -DELTADIST: length of ray from one x or y-side to next x or y-side
*/

void			ray_position(t_base *base, int x)
{
	double	cameraX;
	//printf("rotateleft = %d, rotateright = %d\n", base->game.rotate_left, base->game.rotate_right);
	// if (base->game.rotate == 0) //NEW
	// {
	// 	base->game.planex = (base->game.diry == 0) ? 0 : 0.66;
	// 	base->game.plyneY = (base->game.diry == 0) ? 0.66 : 0;
	// }
    if (base->read.pos == 'W' || base->read.pos == 'S')
		cameraX = (2 * x / (double)base->read.render_x - 1) * -1;
    else
		cameraX = 2 * x / (double)base->read.render_x - 1;
	//printf("Ray pos: dirx[%f], diry [%f], planex[%f], planey[%f]\n", basy->game.dirx, base->game.dirY, base->game.planex, base->game.planey);
	base->game.raydirx = base->game.dirx + base->game.planex * cameraX;
    base->game.raydiry = base->game.diry + base->game.planey * cameraX;
    base->game.mapx = (int)base->read.x_pos;
	base->game.mapy = (int)base->read.y_pos;
	//printf("Mapy = [%d]\n", base->game.mapy);
    base->game.deltadistx = fabs(1 / base->game.raydirx);
    base->game.deltadisty = fabs(1 / base->game.raydiry);
}

//draw the pixels of the stripe as a vertical line //and calculate first
void				raycasting(t_base *base)
{
	int x;

	base->zbuffer = (double *)malloc(sizeof(double) * base->read.render_x); // --> LOCATION OF MALLOC MATTERS! //FREEEE
	if (base->zbuffer == NULL)
		exit_game(base, 1, 27);
	x = 0;
	while(x < base->read.render_x)
	{
		ray_position(base, x);
		initial_step_sidedist(base);
		DDA(base);
		verLine(base, x);
		zbuffer(base, x);
	  	x++;
	}
	base->game.oldtime = base->game.time;
	base->game.time = clock();
	if (base->game.time == -1)
		exit_game(base, 1, 28);
	base->game.frametime = (base->game.time - base->game.oldtime) / CLOCKS_PER_SEC;
	base->game.movespeed = base->game.frametime * 25.0; 
	base->game.rotspeed = base->game.frametime * 5.0;
}

static void		rotate(t_game *game)
{
	double		olddirx;
	double		oldplanex;
	
	if (game->rotate_right == 1)
	{
		olddirx = game->dirx;
		game->dirx = game->dirx * cos(game->rotspeed) - game->diry * sin(game->rotspeed);
		game->diry = olddirx * sin(game->rotspeed) + game->diry * cos(game->rotspeed);
		oldplanex = game->planex;
		game->planex = game->planex * cos(game->rotspeed) - game->planey * sin(game->rotspeed);
		game->planey = oldplanex * sin(game->rotspeed) + game->planey * cos(game->rotspeed);
	}
	if (game->rotate_left == 1)
	{
		olddirx = game->dirx;
		game->dirx = game->dirx * cos(-game->rotspeed) - game->diry * sin(-game->rotspeed);
		game->diry = olddirx * sin(-game->rotspeed) + game->diry * cos(-game->rotspeed);
		oldplanex = game->planex;
		game->planex = game->planex * cos(-game->rotspeed) - game->planey * sin(-game->rotspeed);
		game->planey = oldplanex * sin(-game->rotspeed) + game->planey * cos(-game->rotspeed);
	}
}

void			move(t_base *base, t_game *game)
{
	if (game->move_front == 1)
	{
		if (TWOD[(int)base->read.y_pos][(int)(base->read.x_pos + game->dirx * game->movespeed)] == '+')
			base->read.x_pos += game->dirx * game->movespeed;		//EW
		if (TWOD[(int)(base->read.y_pos + game->diry * game->movespeed)][(int)base->read.x_pos] == '+')
			base->read.y_pos += game->diry * game->movespeed;		//SN
	}
	if (game->move_back == 1)
	{
		if (TWOD[(int)base->read.y_pos][(int)(base->read.x_pos - game->dirx * game->movespeed)] == '+')
			base->read.x_pos -= game->dirx * game->movespeed;
		if (TWOD[(int)(base->read.y_pos - game->diry * game->movespeed)][(int)base->read.x_pos] == '+')
			base->read.y_pos -= game->diry * game->movespeed;
	}
	if (game->move_right == 1)
	{
		if (TWOD[(int)base->read.y_pos][(int)(base->read.x_pos - game->diry * game->movespeed)] == '+')
			base->read.x_pos -= game->diry * game->movespeed;		//S N
		if (TWOD[(int)(base->read.y_pos + base->game.dirx * game->movespeed)][(int)base->read.x_pos] == '+')
			base->read.y_pos += game->dirx * game->movespeed;		//E W
	}
	if (base->game.move_left == 1)
	{
		if (TWOD[(int)base->read.y_pos][(int)(base->read.x_pos + game->diry * game->movespeed)] == '+')
			base->read.x_pos += game->diry * game->movespeed;	//S N
		if (TWOD[(int)(base->read.y_pos - game->dirx * game->movespeed)][(int)base->read.x_pos] == '+')
			base->read.y_pos -= game->dirx * game->movespeed;	//E W
	}
	if (game->rotate_left == 1 || game->rotate_right == 1)
		rotate(game);
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
	if (base->mlx.img == NULL)
			exit_game(base, 1, 26);
	base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bpp, &base->mlx.line_length, &base->mlx.endian);
	if (base->game.update)
		move(base, &base->game);
	floor_ceiling_smooth(base, &base->read);
	raycasting(base);
	sprite(base, &base->sprite);
	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
	base->game.update = 0;
	return (0);
}
