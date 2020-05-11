/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/11 10:14:43 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

static void			verLine(t_base *base, t_tex_co *tex_co, int x)
{
	int		texy;
	int		color;
	int		y;

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

static void			DDA(t_game *game, char **array)
{
    int		hit;
	
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
	double	cameraX;

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
void				raycasting(t_base *base, t_game *game, t_read *read)
{
	int		x;
	double	frametime;
	double	oldtime;

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
