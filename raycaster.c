/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/06 22:09:50 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Reversed my_mlx_pixel_put-dest formula.
** We got the addr of the texture. So we can get the pixel color of a certain
** texturecoordinate. Coordinate color = addr + coordinate.
** tex[i] --> no 0, ea 1, so 2, we 3,
*/

static int		texture_pick_wallside(t_tex *tex, int texx, int texy, int i)
{
	char	*dest;
	int		color;
	
	dest = tex[i].xpm_addr + (texy * tex[i].xpm_line_length + texx *
		(tex[i].xpm_bpp / 8));
	color = *(unsigned int*)dest;
	if (i == 1 || i == 3)
		color = (color >> 1) & 8355711;
	return (color);
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

static void		texture_coordinates_wall(t_tex_co *tex_co, t_wall *wall,
											t_game *game, int render_y)
{
	tex_co->texx = wall->wallx * (double)game->texwidth; //(int)Wallx !!!! Hierna een texture!
    if (game->side == 0 && game->raydirx > 0)
		tex_co->texx = game->texwidth - tex_co->texx - 1;
    if (game->side == 1 && game->raydiry < 0)
		tex_co->texx = game->texwidth - tex_co->texx - 1;
	tex_co->step = 1.0 * game->texheight / wall->lineheight;
    tex_co->texpos = (wall->drawstart - render_y / 2 + wall->lineheight / 2)
		* tex_co->step;
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

static void		draw_calculations_wall(t_read *read, t_game *game,
											t_wall *wall)
{
	if (game->side == 0)
		wall->perpwalldist = (game->mapx -read->x_pos + (1 - game->stepx) / 2)
			/ game->raydirx;
	else
		wall->perpwalldist = (game->mapy - read->y_pos + (1 - game->stepy) / 2)
			/ game->raydiry;
	wall->perpwalldist = (wall->perpwalldist < 1) ? 1 : wall->perpwalldist;
	wall->lineheight = (int)(read->render_y / wall->perpwalldist);
	wall->drawstart = -wall->lineheight / 2 + read->render_y / 2;
	if(wall->drawstart < 0)
		wall->drawstart = 0;
	wall->drawend = wall->lineheight / 2 + read->render_y / 2;
	if(wall->drawend >= read->render_y)
		wall->drawend = read->render_y - 1;
    if (game->side == 0)
 	 	wall->wallx = read->y_pos + wall->perpwalldist * game->raydiry;
    else
		wall->wallx = read->x_pos + wall->perpwalldist * game->raydirx;
    wall->wallx -= (int)wall->wallx;
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

static void		verLine(t_base *base, t_tex_co *tex_co, int x)
{
	int			texy;
	int			color;
	int			y;

	draw_calculations_wall(&base->read, &base->game, &base->wall);
	texture_coordinates_wall(tex_co, &base->wall, &base->game,
		base->read.render_y);
    y = base->wall.drawstart;
	while (y < base->wall.drawend)
    {
        texy = (int)base->tex_co.texpos & (base->game.texheight - 1);
        tex_co->texpos += tex_co->step;
		color = texture_pick_wallside(base->tex, tex_co->texx, texy,
			base->game.tex_side);
		my_mlx_pixel_put(&base->mlx, x, y, color);
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

static void		DDA(t_game *game, char **array)
{
    int			hit;
	
	hit = 0;
   	while (hit == 0)
	{
    	if (game->sidedistx < game->sidedisty)
    	{
    		game->sidedistx += game->deltadistx;
    		game->mapx += game->stepx;
    		game->side = 0;
			game->tex_side = game->stepx < 0 ? 1 : 3;
    	}
    	else
    	{
        	game->sidedisty += game->deltadisty;
        	game->mapy += game->stepy;
        	game->side = 1;
			game->tex_side = game->stepy < 0 ? 2 : 0;
    	}
		if (array[game->mapy][game->mapx] == '1')
			hit = 1;
	}
}

/*
** Calculate step and initial sideDist
*/

static void			initial_step_sidedist(t_read *read, t_game *game)
{
    if(game->raydirx < 0)
    {
    	game->stepx = -1;
    	game->sidedistx = (read->x_pos - game->mapx) * game->deltadistx;
    }
    else
    {
		game->stepx = 1;
    	game->sidedistx = (game->mapx + 1.0 - read->x_pos) * game->deltadistx;
    }
    if(game->raydiry < 0)
    {
		game->stepy = -1;
		game->sidedisty = (read->y_pos - game->mapy) * game->deltadisty;
    }
    else
    {
    	game->stepy = 1;
    	game->sidedisty = (game->mapy + 1.0 - read->y_pos) * game->deltadisty;
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

static void			ray_position(t_read *read, t_game *game, int x)
{
	double		cameraX;

    if (read->pos == 'W' || read->pos == 'S')
		cameraX = (2 * x / (double)read->render_x - 1) * -1;
    else
		cameraX = 2 * x / (double)read->render_x - 1;
	game->raydirx = game->dirx + game->planex * cameraX;
    game->raydiry = game->diry + game->planey * cameraX;
    game->mapx = (int)read->x_pos;
	game->mapy = (int)read->y_pos;
    game->deltadistx = fabs(1 / game->raydirx);
    game->deltadisty = fabs(1 / game->raydiry);
}

//draw the pixels of the stripe as a vertical line //and calculate first
static void		raycasting(t_base *base, t_game *game, t_read *read)
{
	int			x;
	double		frametime;
	double		oldtime;

	base->zbuffer = (double *)malloc(sizeof(double) * read->render_x);
	if (base->zbuffer == NULL)
		exit_game(base, 1, 27);
	x = 0;
	while(x < read->render_x)
	{
		ray_position(read, game, x);
		initial_step_sidedist(read, game);
		DDA(game, read->array);
		verLine(base, &base->tex_co, x);
		base->zbuffer[x] = base->wall.perpwalldist;
	  	x++;
	}
	oldtime = game->time;
	game->time = clock();
	if (game->time == -1)
		exit_game(base, 1, 28);
	frametime = (game->time - oldtime) / CLOCKS_PER_SEC;
	game->movespeed = frametime * 25.0; 
	game->rotspeed = frametime * 5.0;
}

static void			move_rotate(t_game *game, t_read *read, char **array)
{
	if (game->move_front == 1)
		move_front(game, read, array);
	if (game->move_back == 1)
		move_back(game, read, array);
	if (game->move_right == 1)
		move_right(game, read, array);
	if (game->move_left == 1)
		move_left(game, read, array);
	if (game->rotate_right == 1)
		rotate_right(game);
	if (game->rotate_left == 1)
		rotate_left(game);
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
		move_rotate(&base->game, &base->read, base->read.array);
	floor_ceiling_smooth(&base->mlx, &base->read);
	raycasting(base, &base->game, &base->read);
	sprite(base, &base->sprite, &base->game, &base->read);
	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
	base->game.update = 0;
	return (0);
}
