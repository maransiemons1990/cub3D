/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/09 13:36:12 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/14 15:17:42 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Sprites are 2D pictures always facing to you
*/

#include "cub3d.h"

void            zbuffer(t_base *base, int x)
{
	//1D Zbuffer
	//double    ZBuffer[base->read.render_x];
	
	//SET THE ZBUFFER FOR THE SPRITE CASTING
  base->ZBuffer[x] = base->wall.perpWallDist;
}

void            sortSprites(int *order, double *dist, int amount)
{
  int i;
  int j;
  double a;
  int b;

  i = 0;
  while (i < amount)
  {
    j = i + 1;
    while(j < amount)
    {
      if (dist[i] < dist[j])
      {
        a =  dist[i];
        dist[i] = dist[j];
        dist[j] = a;
        
        b =  order[i];
        order[i] = order[j];
        order[j] = b;
      }
      j++;
    } 
    i++;
  }
}

void            sprite(t_base *base)
{
  int       i;
  int       numSprites;
  numSprites = 3;
  int       spriteOrder[numSprites];
  double    spriteDistance[numSprites];
  t_sprite  sprite[3];

  i = 0;
  sprite[0].x = 29; //#0
  sprite[0].y = 16;
  sprite[1].x = 37; //#1
  sprite[1].y = 17;
  sprite[2].x = 29; //#2
  sprite[2].y = 18;
  //SPRITE CASTING
  //sort sprites from far to close
  while (i < numSprites)
  {
      spriteOrder[i] = i;
      spriteDistance[i] = ((base->read.x_pos - sprite[i].x) * (base->read.x_pos - sprite[i].x) + (base->read.y_pos - sprite[i].y) * (base->read.y_pos - sprite[i].y));
      //printf("spriteOrder[%d] = [%d] | spritedistance[%d] = [%f]\n", i, spriteOrder[i] = i, i, spriteDistance[i]);
      i++;
  }
  //function used to sort the sprites
  sortSprites(spriteOrder, spriteDistance, numSprites);
  
  i = 0;
  while (i < numSprites)
  {
    //translate sprite position to relative to camera
    double spriteX = sprite[spriteOrder[i]].x - base->read.x_pos;
    double spriteY = sprite[spriteOrder[i]].y - base->read.y_pos;

    //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

    double invDet = 1.0 / (base->game.planeX * base->game.dirY - base->game.dirX * base->game.planeY); //required for correct matrix multiplication

    double transformX = invDet * (base->game.dirY * spriteX - base->game.dirX * spriteY);
    double transformY = invDet * (-base->game.planeY * spriteX + base->game.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

    int spriteScreenX = (int)((base->read.render_x / 2) * (1 + transformX / transformY));
    

    //parameters for scaling and moving the sprites
    #define uDiv 1
    #define vDiv 1
    #define vMove 0.0
    int vMoveScreen = (int)(vMove / transformY);
      
    //calculate height of the sprite on screen
    int spriteHeight = abs((int)(base->read.render_y / (transformY)))/ vDiv; //using "transformY" instead of the real distance prevents fisheye
    
    //calculate lowest and highest pixel to fill in current stripe
    int drawStartY = -spriteHeight / 2 + base->read.render_y/ 2 + vMoveScreen;
    if (drawStartY < 0)
      drawStartY = 0;
    int drawEndY = spriteHeight / 2 + base->read.render_y / 2 + vMoveScreen;
    if (drawEndY >= base->read.render_y)
      drawEndY = base->read.render_y - 1;

    //calculate width of the sprite
    int spriteWidth = abs( (int)(base->read.render_y / (transformY))) / uDiv;
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0)
      drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= base->read.render_x)
      drawEndX = base->read.render_y - 1;
    
    //loop through every vertical stripe of the sprite on screen
    int stripe;
    stripe = drawStartX;
    int color;
    char *dest;
    
    while (stripe < drawEndX)
    {
      
      int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * base->game.texWidth / spriteWidth) / 256;
      //the conditions in the if are:
      //1) it's in front of camera plane so you don't see things behind you
      //2) it's on the screen (left)
      //3) it's on the screen (right)
      //4) ZBuffer, with perpendicular distance
      
      if (transformY > 0 && stripe > 0 && stripe < base->read.render_x && transformY < base->ZBuffer[stripe])
      {
        int y;

        y = drawStartY;
        while (y < drawEndY) //for every pixel of the current stripe
        {
          int d = (y - vMoveScreen) * 256 - base->read.render_y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * base->game.texHeight) / spriteHeight) / 256;
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
  }
}



/*



Uint32 buffer[screenHeight][screenWidth]; // y-coordinate first because it works per scanline


/
    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < numSprites; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = sprite[spriteOrder[i]].x - posX;
      double spriteY = sprite[spriteOrder[i]].y - posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY); 
	  //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

      int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

      //parameters for scaling and moving the sprites
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = int(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs(int(h / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawEndY >= h) drawEndY = h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( int (h / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= w) drawEndX = w - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
          Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
    }

	//sort the sprites based on distance
void sortSprites(int* order, double* dist, int amount)
{
  std::vector<std::pair<double, int>> sprites(amount);
  for(int i = 0; i < amount; i++) {
    sprites[i].first = dist[i];
    sprites[i].second = order[i];
  }
  std::sort(sprites.begin(), sprites.end());
  // restore in reverse order to go from farthest to nearest
  for(int i = 0; i < amount; i++) {
    dist[i] = sprites[amount - i - 1].first;
    order[i] = sprites[amount - i - 1].second;
  }
}

*/