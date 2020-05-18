/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 13:36:12 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/13 17:50:25 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** 3rd while: for every pixel of the current stripe.
** d: 256 and 128 factors to avoid floats.
** Dest: Reversed my_mlx_pixel_put-dest formula.
** We got the addr of the sprite. So we can get the pixel color of a certain
** spritecoordinate. Coordinate color = addr + coordinate.
** Draw pixel if it isn't black, black is the invisible color. Otherwise the
** sprites will be rectangles.
** Tex[4] is sprite texture.
*/

static void		draw_vertical_stripe(int texx, int stripe, t_base *base,
										t_sprite *sprite)
{
	int			texy;
	int			y;
	int			d;
	int			color;
	char		*dest;

	y = sprite->drawstarty;
	while (y < sprite->drawendy)
	{
		d = (y - sprite->vmovescreen) * 256 - base->read.render_y * 128
			+ sprite->spr_height * 128;
		texy = ((d * base->game.texheight) / sprite->spr_height) / 256;
		dest = base->tex[4].xpm_addr + (texy * base->tex[4].xpm_line_length
			+ texx * (base->tex[4].xpm_bpp / 8));
		color = *(unsigned int*)dest;
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&base->mlx, stripe, y, color);
		y++;
	}
}

/*
** Calculate the size of the sprite on the screen (both in x and y direction)
** by using the perpendicular distance:
** SpriteHeight: calculate height of the sprite on screen using yform
** instead of the real distance prevents fisheye.
** DrawStart/DrawEnd: calculate lowest and highest pixel to fill in current
** stripe.
** SpriteWidth: calculate width of the sprite.
*/

static void		calculate_size_sprite_screen(t_sprite *sprite, int render_x,
												int render_y)
{
	sprite->spr_height = abs((int)(render_y / (sprite->yform))) / VDIV;
	sprite->drawstarty = -sprite->spr_height / 2 + render_y / 2
		+ sprite->vmovescreen;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = sprite->spr_height / 2 + render_y / 2
		+ sprite->vmovescreen;
	if (sprite->drawendy >= render_y)
		sprite->drawendy = render_y - 1;
	sprite->spr_width = abs((int)(render_y / (sprite->yform))) / UDIV;
	sprite->drawstartx = -sprite->spr_width / 2 + sprite->spr_screenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = sprite->spr_width / 2 + sprite->spr_screenx;
	if (sprite->drawendx >= render_x)
		sprite->drawendx = render_y - 1;
}

/*
** Project the sprite on the camera plane (in 2D):
** SpriteX: subtract the player's position from the sprite's position,
** then you have the position of the sprite relative to the player (camera).
** InvDet/xform: Then it has to be rotated so that the direction is
** relative to the player. Therefore we transform the sprite with the
** inverse camera matrix.
** 		InvDet: required for correct matrix multiplication.
** 		xform: X coordinate of the sprite in camera space.
** 		yform: Y coordinate of the sprite in camera space.
**      	Y is the depth inside the screen (that what Z is in 3D).
** SpritescreenX: To project it on screen, divide X through the depth,
** and then translate and scale it so that it's in pixel coordinates.
** Parameters for scaling and moving the sprites:
** - UDIV and VDIV: to shrink the sprite
** - vMove: to move the sprite down if it has to stand on the floor,
**   or up if it has to hang on the ceiling.
** - vMoveScreen is vMove projected on the screen by dividing it through
** the depth.
*/

static void		project_sprite(t_sprite *sprite, t_ll_sprite *ll_sprite,
									t_game *game, t_read *read)
{
	double		spritex;
	double		spritey;
	double		invdet;
	double		xform;

	spritex = ll_sprite->x - read->x_pos;
	spritey = ll_sprite->y - read->y_pos;
	invdet = 1.0 / (game->planex * game->diry - game->dirx * game->planey);
	if (read->pos == 'W' || read->pos == 'S')
		xform = (invdet * (game->diry * spritex - game->dirx * spritey) * -1);
	else
		xform = invdet * (game->diry * spritex - game->dirx * spritey);
	sprite->yform = invdet * (-game->planey * spritex + game->planex
		* spritey);
	sprite->spr_screenx = (int)((read->render_x / 2)
		* (1 + xform / sprite->yform));
	sprite->vmovescreen = (int)(VMOVE / sprite->yform);
}

/*
** Sprites are 2D pictures always facing to you.
** 1st while: loop per sprite.
** Project the sprite on the camera plane (in 2D).
** Calculate the size of the sprite on the screen (in x and y direction)
** by using the perpendicular distance.
** 2nd While: loop through every vertical stripe of the sprite on screen.
** Per x <--------------> (width of sprite).
** If conditions are met: Draw the sprites vertical stripe by vertical
** stripe.
** The conditions in the if are:
** 1) it's in front of camera plane so you don't see things behind you
** 2) it's on the screen (left)
** 3) it's on the screen (right)
** 4) Distance is smaller than the 1D ZBuffer(with perpendicular distance)
** of the walls of the current stripe. Don't draw the vertical stripe if the
** distance is further away than the 1D ZBuffer of the walls of the current
** stripe.
** You don't have to update the ZBuffer while drawing the stripes: since
** they're sorted, the ones closer to you will be drawn last,
** so they're drawn over the further away ones.
*/

void			sprite(t_base *base, t_sprite *sprite, t_game *game,
							t_read *read)
{
	int			i;
	int			texx;
	int			stripe;
	t_ll_sprite	*ll_sprite;

	i = 0;
	ll_sprite = base->head;
	while (i < read->nb_sprites)
	{
		project_sprite(sprite, ll_sprite, game, read);
		calculate_size_sprite_screen(sprite, read->render_x, read->render_y);
		stripe = sprite->drawstartx;
		while (stripe < sprite->drawendx)
		{
			texx = (int)(256 * (stripe -
				(-sprite->spr_width / 2 + sprite->spr_screenx)) *
				game->texwidth / sprite->spr_width) / 256;
			if (sprite->yform > 0 && stripe > 0 && stripe < read->render_x
				&& sprite->yform < base->zbuffer[stripe])
				draw_vertical_stripe(texx, stripe, base, &base->sprite);
			stripe++;
		}
		i++;
		ll_sprite = ll_sprite->next;
	}
}
