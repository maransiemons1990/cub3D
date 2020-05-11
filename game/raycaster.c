/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 10:58:10 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/11 14:58:03 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Draw the pixels as a vertical line.
** Texy: Cast the texture coordinate to integer, and mask with (texheight - 1)
** in case of overflow.
** Texpos: Starting texture coordinate. Every y increase, change with a step.
** Check which side the ray hit the wall. This determines which texture is used
** as color.
** my_mlx: set wall coordinate to new color.
*/

static void			verline(t_base *base, t_tex_co *tex_co, int x)
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
** Perform Digital Differential Analysis (DDA)
** Jump to next map square, in x-direction OR in y-direction.
** if --> jump in X direction.
** else --> jump in Y direction.
** Hit: check if ray has hit a wall.
*/

static void			dda(t_game *game, char **array)
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
** Calculate step and initial sidedist
*/

static void			initial_step_sidedist(t_read *read, t_game *game)
{
	if (game->raydirx < 0)
	{
		game->stepx = -1;
		game->sidedistx = (read->x_pos - game->mapx) * game->deltadistx;
	}
	else
	{
		game->stepx = 1;
		game->sidedistx = (game->mapx + 1.0 - read->x_pos) * game->deltadistx;
	}
	if (game->raydiry < 0)
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
** Camerax: x-coordinate in camera space.
** To prevent a mirrored image if West or South, camerax * -1.
** Raydir: calculate ray position and direction.
** Mapx & -y: which box of the map we're in.
** Deltadist: length of ray from one x or y-side to next x or y-side.
*/

static void			ray_position(t_read *read, t_game *game, int x)
{
	double	camerax;

	if (read->pos == 'W' || read->pos == 'S')
		camerax = (2 * x / (double)read->render_x - 1) * -1;
	else
		camerax = 2 * x / (double)read->render_x - 1;
	game->raydirx = game->dirx + game->planex * camerax;
	game->raydiry = game->diry + game->planey * camerax;
	game->mapx = (int)read->x_pos;
	game->mapy = (int)read->y_pos;
	game->deltadistx = fabs(1 / game->raydirx);
	game->deltadisty = fabs(1 / game->raydiry);
}

/*
** Zbuffer: while raycasting the walls, store the perpendicular distance of
** each vertical stripe in a 1D ZBuffer. Because the ZBuffer is 1D and can
** only detect if the sprite is in front or behind a wall.
*/

void				raycasting(t_base *base, t_game *game, t_read *read)
{
	int		x;
	double	frametime;
	double	oldtime;

	x = 0;
	while (x < read->render_x)
	{
		ray_position(read, game, x);
		initial_step_sidedist(read, game);
		dda(game, read->array);
		verline(base, &base->tex_co, x);
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
