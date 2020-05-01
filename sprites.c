/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 13:36:12 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/01 09:23:19 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Sprites are 2D pictures always facing to you.
**
** Parameters for scaling and moving the sprites:
** - uDiv and vDiv: to shrink the sprite
** - vMove: to move the sprite down if it has to stand on the floor,
**   or up if it has to hang on the ceiling.
** - vMoveScreen is vMove projected on the screen by dividing it through the depth.
**
** default: 1, 1, 0.0
** uDiv = 2, vDiv = 2, vMove = 0.0, the sprites are half as big, and float.
** Put it back on the ground by setting vMove to 64.0 (the size of the texture).
** 
*/
#define uDiv 1
#define vDiv 1
#define vMove 0.0


/*
** While raycasting the walls, store the perpendicular distance of each
** vertical stripe in a 1D ZBuffer.
** Because the ZBuffer is 1D and can only detect if the sprite is in front or behind a wall.
** Later we draw the sprites vertical stripe by vertical stripe, don't draw the
** vertical stripe if the distance is further away than the 1D ZBuffer of the walls of the current stripe
** >>> Ik denk dat dit overbodig is bij mij omdat ik geen sprites opsla die niet in mijn flood fill zitten!!!<<<
** hmm maar er zijn wel waarden die hij uitlsuit. Af en toe base->sprite.transformy niet kleiner dan Zbuffer!
** You don't have to update the ZBuffer while drawing the stripes: since they're sorted, 
** the ones closer to you will be drawn last, so they're drawn over the further away ones.
*/

void            zbuffer(t_base *base, int x)
{
  base->ZBuffer[x] = base->wall.perpWallDist;
}

/*
** - 3rd while: for every pixel of the current stripe.
** - d: 256 and 128 factors to avoid floats.
** - Dest: Reversed my_mlx_pixel_put-dest formula.
** We got the addr of the sprite. So we can get the pixel color of a certain
** spritecoordinate. Coordinate color = addr + coordinate.
** - Draw pixel if it isn't black, black is the invisible color.
**   Otherwise the sprites will be rectangles.
** tex[4] is sprite texture.
*/

static void         draw_vertical_stripe_sprite(int texx, int stripe, t_base *base)
{
  int       texY;
  int       y;
  int       d;
  int       color;
  char      *dest;
  
  y = base->sprite.drawstarty;
  while (y < base->sprite.drawendy)
  {
    d = (y - base->sprite.vmovescreen) * 256 - base->read.render_y * 128 + base->sprite.spriteheight * 128; 
    texY = ((d * base->game.texHeight) / base->sprite.spriteheight) / 256;
    dest = base->tex[4].xpm_addr + (texY * base->tex[4].xpm_line_length + texx * (base->tex[4].xpm_bpp / 8));
		color = *(unsigned int*)dest;
    if ((color & 0x00FFFFFF) != 0)
      my_mlx_pixel_put(base, stripe, y, color);
    y++;
  }
}

/*
** Calculate the size of the sprite on the screen (both in x and y direction)
** by using the perpendicular distance:
**
** - SpriteHeight: calculate height of the sprite on screen 
**    --> using TransformY instead of the real distance prevents fisheye.
** - DrawStart/DrawEnd: calculate lowest and highest pixel to fill in current stripe
** - SpriteWidth: calculate width of the sprite.
*/

void            calculate_size_sprite_screen(t_base *base)
{
  base->sprite.spriteheight = abs((int)(base->read.render_y / (base->sprite.transformy)))/ vDiv; 
  base->sprite.drawstarty = -base->sprite.spriteheight / 2 + base->read.render_y/ 2 + base->sprite.vmovescreen;
  if (base->sprite.drawstarty < 0)
    base->sprite.drawstarty = 0;
  base->sprite.drawendy = base->sprite.spriteheight / 2 + base->read.render_y / 2 + base->sprite.vmovescreen;
  if (base->sprite.drawendy >= base->read.render_y)
    base->sprite.drawendy = base->read.render_y - 1;
  base->sprite.spritewidth = abs( (int)(base->read.render_y / (base->sprite.transformy))) / uDiv;
  base->sprite.drawstartx = -base->sprite.spritewidth / 2 + base->sprite.spritescreenx;
  if (base->sprite.drawstartx < 0)
    base->sprite.drawstartx = 0;
  base->sprite.drawendx = base->sprite.spritewidth / 2 + base->sprite.spritescreenx;
  if (base->sprite.drawendx >= base->read.render_x)
    base->sprite.drawendx = base->read.render_y - 1;
}

/*
** Project the sprite on the camera plane (in 2D):
**
** - SpriteX: subtract the player's position from the sprite's position,
** then you have the position of the sprite relative to the player (camera).
** - InvDet/TransformX: Then it has to be rotated so that the direction is
** relative to the player. Therefore we transform the sprite with the
** inverse camera matrix.
** *    InvDet --> required for correct matrix multiplication.
** *    TrasformX --> X coordinate of the sprite in camera space.
** *    TransformY --> Y coordinate of the sprite in camera space. 
**          Y is the depth inside the screen (that what Z is in 3D).
** - SpritescreenX: To project it on screen, divide X through the depth,
**  and then translate and scale it so that it's in pixel coordinates.
** - VMoveScreen: is vMove projected on the screen by dividing 
**   it through the depth.
** *    vMove to move the sprite down if it has to stand on the floor,
**      or up if it has to hang on the ceiling.
*/

static void         project_sprite_on_cameraplane2d(t_sprite  *sprite, t_base *base)
{
  double    spritex;
  double    spritey;
  double    invdet;
  double    transformx;

  spritex = sprite->x - base->read.x_pos; //
  spritey = sprite->y - base->read.y_pos;
  invdet = 1.0 / (base->game.planeX * base->game.dirY - base->game.dirX * base->game.planeY);
  transformx = invdet * (base->game.dirY * spritex - base->game.dirX * spritey);
  base->sprite.transformy = invdet * (-base->game.planeY * spritex + base->game.planeX * spritey);
  base->sprite.spritescreenx = (int)((base->read.render_x / 2) * (1 + transformx / base->sprite.transformy));
  base->sprite.vmovescreen = (int)(vMove / base->sprite.transformy);  //
}

/*
**  - 1st while: loop per sprite.
**  - Project the sprite on the camera plane (in 2D).
**  - Calculate the size of the sprite on the screen (in x and y direction)
**  by using the perpendicular distance.
**  - 2nd While: loop through every vertical stripe of the sprite on screen.
**      --> per x <--------------> (width of sprite).
**  - IF conditions are met: Draw the sprites vertical stripe by vertical
**  stripe.
**  - The conditions in the if are:
**  1) it's in front of camera plane so you don't see things behind you
**  2) it's on the screen (left)
**  3) it's on the screen (right)
**  4) Distance is smaller than the 1D ZBuffer(with perpendicular distance) of the walls of the current stripe
*/

void            sprite(t_base *base)
{
  int       i;
  int       texx;
  int       stripe;
  t_sprite  *sprite;

  i = 0;
  sprite = base->head;
  while (i < base->read.nb_sprites)
  {
    project_sprite_on_cameraplane2d(sprite, base);
    calculate_size_sprite_screen(base);
    stripe = base->sprite.drawstartx;
    while (stripe < base->sprite.drawendx)
    {
      texx = (int)(256 * (stripe - (-base->sprite.spritewidth / 2 + base->sprite.spritescreenx)) * base->game.texWidth / base->sprite.spritewidth) / 256;
      if (base->sprite.transformy > 0 && stripe > 0 && stripe < base->read.render_x && base->sprite.transformy < base->ZBuffer[stripe])
        draw_vertical_stripe_sprite(texx, stripe, base);
      stripe++;
    }
    i++;
    sprite = sprite->next;
  }
}
