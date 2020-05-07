/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 18:32:30 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/07 12:21:50 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Pushing pixels to the window. we will have to buffer all of our pixels to a image
** which we will then push to the window.
** Instead of push the pixel instantly to the window (without waiting for the frame to be entirely rendered).
** Locate postion of pixel: (y * size_line + x * (bits_per_pixel / 8));
** Here we multiply size_line by y as we need to skip y lines (line size does not equal the amount of pixels in a line).
** We then add the remaining x units multiplied by bits_per_pixl / 8 to align with the final location.
*/

void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char    *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}

/*
** Reversed my_mlx_pixel_put-dest formula.
** We got the addr of the texture. So we can get the pixel color of a certain
** texturecoordinate. Coordinate color = addr + coordinate.
** tex[i] --> no 0, ea 1, so 2, we 3,
*/

int			texture_pick_wallside(t_tex *tex, int texx, int texy, int i)
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

void		texture_coordinates_wall(t_tex_co *tex_co, t_wall *wall,
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

void		draw_calculations_wall(t_read *read, t_game *game, t_wall *wall)
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
