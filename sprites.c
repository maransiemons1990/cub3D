/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 13:36:12 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/15 22:09:47 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
** Sprites are 2D pictures always facing to you
*/

void            zbuffer(t_base *base, int x)
{
	//1D Zbuffer
	//double    ZBuffer[base->read.render_x];
	
	//SET THE ZBUFFER FOR THE SPRITE CASTING
  base->ZBuffer[x] = base->wall.perpWallDist;
}


// void            sortSprites(int *order, double *dist, int amount)
// {
//   int i;
//   int j;
//   double a;
//   int b;

//   i = 0;
//   while (i < amount)
//   {
//     j = i + 1;
//     while(j < amount)
//     {
//       if (dist[i] < dist[j])
//       {
//         a =  dist[i];
//         dist[i] = dist[j];
//         dist[j] = a;
        
//         b =  order[i];
//         order[i] = order[j];
//         order[j] = b;
//       }
//       j++;
//     } 
//     i++;
//   }
// }

//  sprite[0].x = 29; //#0
//   sprite[0].y = 16;
//   sprite[1].x = 37; //#1
//   sprite[1].y = 17;
//   sprite[2].x = 29; //#2
//   sprite[2].y = 18;

  //parameters for scaling and moving the sprites
    #define uDiv 1
    #define vDiv 1
    #define vMove 0.0

void            sprite(t_base *base)
{
  int       i;
  double    spriteX;
  double    spriteY;
  double invDet;
  double transformX;
  double transformY;
  int spriteScreenX;
  int vMoveScreen;
  int spriteHeight;
  int drawStartY;
  int drawEndY;
  int spriteWidth;
  int drawStartX;
  int drawEndX;
  int stripe;
  int color;
  char *dest;
  t_sprite  *sprite;
  int texX;
  int y;
  int d;
  int texY;

  i = 0;
  sprite = base->head; 
  while (i < base->read.nb_sprites)
  {
    //translate sprite position to relative to camera
    spriteX = sprite->x - base->read.x_pos;
    spriteY = sprite->y - base->read.y_pos;

    //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

    invDet = 1.0 / (base->game.planeX * base->game.dirY - base->game.dirX * base->game.planeY); //required for correct matrix multiplication

    transformX = invDet * (base->game.dirY * spriteX - base->game.dirX * spriteY);
    transformY = invDet * (-base->game.planeY * spriteX + base->game.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

    spriteScreenX = (int)((base->read.render_x / 2) * (1 + transformX / transformY));
    vMoveScreen = (int)(vMove / transformY);  
    //calculate height of the sprite on screen
    spriteHeight = abs((int)(base->read.render_y / (transformY)))/ vDiv; //using "transformY" instead of the real distance prevents fisheye
    
    //calculate lowest and highest pixel to fill in current stripe
    drawStartY = -spriteHeight / 2 + base->read.render_y/ 2 + vMoveScreen;
    if (drawStartY < 0)
      drawStartY = 0;
    drawEndY = spriteHeight / 2 + base->read.render_y / 2 + vMoveScreen;
    if (drawEndY >= base->read.render_y)
      drawEndY = base->read.render_y - 1;

    //calculate width of the sprite
    spriteWidth = abs( (int)(base->read.render_y / (transformY))) / uDiv;
    drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0)
      drawStartX = 0;
    drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= base->read.render_x)
      drawEndX = base->read.render_y - 1;
    
    //loop through every vertical stripe of the sprite on screen
    stripe = drawStartX;
    while (stripe < drawEndX)
    {
      
      texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * base->game.texWidth / spriteWidth) / 256;
      //the conditions in the if are:
      //1) it's in front of camera plane so you don't see things behind you
      //2) it's on the screen (left)
      //3) it's on the screen (right)
      //4) ZBuffer, with perpendicular distance
      
      if (transformY > 0 && stripe > 0 && stripe < base->read.render_x && transformY < base->ZBuffer[stripe])
      {
        y = drawStartY;
        while (y < drawEndY) //for every pixel of the current stripe
        {
          d = (y - vMoveScreen) * 256 - base->read.render_y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          texY = ((d * base->game.texHeight) / spriteHeight) / 256;
          //
          //color = texture_pick_wallside(base, base->tex_co.texX, texY);
          dest = base->tex_s.png_addr + (texY * base->tex_no.png_line_length + texX * (base->tex_no.png_bits_per_pixel / 8));
		      color = *(unsigned int*)dest;
          if ((color & 0x00FFFFFF) != 0)//paint pixel if it isn't black, black is the invisible color
		        my_mlx_pixel_put(base, stripe, y, color);
          //[base->game.texWidth * texY + texX]; //get current color from the texture
           // buffer[y][stripe] = color; 
          y++;
        }
      }
      stripe++;
    }
    i++;
    sprite = sprite->next;
  }
}
