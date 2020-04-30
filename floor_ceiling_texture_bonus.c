/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling_texture_bonus.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 14:12:22 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/30 15:55:36 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** -CELL: the cell coord is got from the integer parts of floorX and floorY
** -TX/TY: get the texture coordinate from the fractional part
** -OWN PART: reversed dest formula harm.
** ceiling is symmetrical, at (screenHeight - y - 1) instead of y.
*/

	
	// base->tex_f.png_img = mlx_png_file_to_image(base->mlx.mlx, "./64x/dirt.png", &base->game.texWidth, &base->game.texHeight);
	// base->tex_f.png_addr = mlx_get_data_addr(base->tex_f.png_img, &base->tex_f.png_bits_per_pixel, &base->tex_f.png_line_length, &base->tex_f.png_endian);
	// base->tex_c.png_img = mlx_png_file_to_image(base->mlx.mlx,"./Textures_png/stars.png", &base->game.texWidth, &base->game.texHeight);
	// base->tex_c.png_addr = mlx_get_data_addr(base->tex_c.png_img, &base->tex_c.png_bits_per_pixel, &base->tex_c.png_line_length, &base->tex_c.png_endian);




static void		floor_ceiling_tex_x_loop(t_base *base, int y)
{
	int		x;
	int		cellX;
	int		cellY;
	int		color;
	int		tx;
	int		ty;
	char	*dest;
	
	x = 0;
	while (x < base->read.render_x)
    {
        cellX = (int)(base->floor.floorX);
        cellY = (int)(base->floor.floorY);
        tx = (int)(base->game.texWidth * (base->floor.floorX - cellX)) & (base->game.texWidth - 1);
        ty = (int)(base->game.texHeight * (base->floor.floorY - cellY)) & (base->game.texHeight - 1);
        base->floor.floorX += base->floor.floorStepX;
        base->floor.floorY += base->floor.floorStepY;
		dest = base->tex_f.png_addr + (base->tex_f.png_line_length * ty + tx * (base->tex_we.png_bits_per_pixel / 8));
		color = *(unsigned int*)dest;
		color = (color >> 1) & 8355711;
		my_mlx_pixel_put(base, x, y, color);
        dest = base->tex_c.png_addr + (base->tex_f.png_line_length * ty + tx * (base->tex_we.png_bits_per_pixel / 8));
		color = *(unsigned int*)dest;
		color = (color >> 1) & 8355711;
		my_mlx_pixel_put(base, x, (base->read.render_y - y - 1), color);
		x++;
	}
}

/*
** -RAYDIR: for leftmost ray (x = 0) and rightmost ray (x = width screen)
** -P: Current y position compared to the center of the screen (the horizon)
** -POSZ: Vertical position of the camera. With 0.5, it's exactly in the center
** between floor and ceiling, matching also how the walls are being raycasted.
** -ROWDISTANCE: Horizontal distance from the camera to the floor for the
** current row. 0.5 is the z position exactly in the middle between floor
** and ceiling.
** -FLOORSTEP: calculate the real world step vector we have to add for each x
** (parallel to camera plane). //CHANGED TO render_x to render_y (prettier).
** -FLOOR: real world coordinates of the leftmost column.
** This will be updated as we step to the right.
** 
*/

static void		floor_ceiling_tex_y(t_base *base, int y)
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	posZ;
	float	rowDistance;
	int		p;
	
	rayDirX0 = base->game.dirX - base->game.planeX;
    rayDirY0 = base->game.dirY - base->game.planeY;
    rayDirX1 = base->game.dirX + base->game.planeX;
    rayDirY1 = base->game.dirY + base->game.planeY;
    p = y - base->read.render_y / 2;
    posZ = 0.5 * base->read.render_y;
    rowDistance = posZ / p;
    base->floor.floorStepX = rowDistance * (rayDirX1 - rayDirX0) / base->read.render_y;
    base->floor.floorStepY = rowDistance * (rayDirY1 - rayDirY0) / base->read.render_y;
    base->floor.floorX = base->read.x_pos + rowDistance * rayDirX0; //changed double x_pos
    base->floor.floorY = base->read.y_pos + rowDistance * rayDirY0;
}

/*
** Texturing the floor and ceiling is optional. 
** The subject states a smooth color from the scene file.
** to activate texturing:
** activate the function in function "loop" in raycaster.c
*/

void			floor_ceiling_texture(t_base *base)
{
	int 	y;

	y = base->read.render_y / 2 + 1;
	while (y < base->read.render_y)
    {
		floor_ceiling_tex_y(base, y);
		floor_ceiling_tex_x_loop(base, y);
	  	y++;
    }
}
