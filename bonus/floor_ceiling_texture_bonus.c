/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling_texture_bonus.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 14:12:22 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/12 23:41:53 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** -CELL: the cell coord is got from the integer parts of floorx and floory
** -TX/TY: get the texture coordinate from the fractional part
** -OWN PART: reversed dest formula harm.
** ceiling is symmetrical, at (screenHeight - y - 1) instead of y.
*/

	
	// base->tex_f.png_img = mlx_png_file_to_image(base->mlx.mlx, "./64x/dirt.png", &base->game.texWidth, &base->game.texHeight);
	// base->tex_f.png_addr = mlx_get_data_addr(base->tex_f.png_img, &base->tex_f.png_bits_per_pixel, &base->tex_f.png_line_length, &base->tex_f.png_endian);
	// base->tex_c.png_img = mlx_png_file_to_image(base->mlx.mlx,"./Textures_png/stars.png", &base->game.texWidth, &base->game.texHeight);
	// base->tex_c.png_addr = mlx_get_data_addr(base->tex_c.png_img, &base->tex_c.png_bits_per_pixel, &base->tex_c.png_line_length, &base->tex_c.png_endian);

//i = 5: Ceiling, i = 6: Floor.

static void		get_tex_coordinate(t_game *game, t_floor *floor)
{
	int		cellx;
	int		celly;

	cellx = (int)(floor->floorx);
	celly = (int)(floor->floory);
	floor->tx = (int)(game->texwidth * (floor->floorx - cellx))
		& (game->texwidth - 1);
	floor->ty = (int)(game->texheight * (floor->floory - celly))
		& (game->texheight - 1);
	floor->floorx += floor->floorstepx;
	floor->floory += floor->floorstepy;	
}

static void		floor_ceiling_tex_x_loop(t_base *base, t_floor *floor,
											t_tex *tex_fc, int y)
{
	int		color;
	int		x;
	int		i;

	x = 0;
	while (x < base->read.render_x)
	{
		i = 0;
		get_tex_coordinate(&base->game, floor);
		while (i < 2)
		{
			color = texture_pick(tex_fc, floor->tx, floor->ty, i);
			if (i == 0)
				my_mlx_pixel_put(&base->mlx, x, y, color);
			else
				my_mlx_pixel_put(&base->mlx, x, (base->read.render_y - y - 1)
					, color);
			i++;
		}
		x++;
	}
}

/*
** -RAYdIR: for leftmost ray (x = 0) and rightmost ray (x = width screen)
** -P: Current y position compared to the center of the screen (the horizon)
** -POSz: Vertical position of the camera. With 0.5, it's exactly in the center
** between floor and ceiling, matching also how the walls are being raycasted.
** -ROWdISTANCE: Horizontal distance from the camera to the floor for the
** current row. 0.5 is the z position exactly in the middle between floor
** and ceiling.
** -FLOORSTEP: calculate the real world step vector we have to add for each x
** (parallel to camera plane). //CHANGED TO render_x to render_y (prettier).
** -FLOOR: real world coordinates of the leftmost column.
** This will be updated as we step to the right.
*/

static void		floor_ceiling_tex_y(t_read *read, t_game *game, t_floor *floor
										, int y)
{
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	
	raydirx0 = game->dirx - game->planex;
	raydirx1 = game->dirx + game->planex;
	raydiry0 = game->diry - game->planey;
	raydiry1 = game->diry + game->planey;
	floor->p = y - read->render_y / 2;
	floor->posz = 0.5 * read->render_y;
	floor->rowdistance = floor->posz / floor->p;
	floor->floorstepx = floor->rowdistance * (raydirx1 - raydirx0)
		/ read->render_y;
	floor->floorstepy = floor->rowdistance * (raydiry1 - raydiry0)
		/ read->render_y;
	floor->floorx = read->x_pos + floor->rowdistance * raydirx0; //changed double x_pos
	floor->floory = read->y_pos + floor->rowdistance * raydiry0;
}

/*
** Texturing the floor and ceiling is optional. 
** The subject states a smooth color from the scene file.
** to activate texturing:
** activate the function in function "loop" in raycaster.c
*/



/*
** mlx_png_file_to_image currently leaks memory. Therefore using xpm function
** instead.
** i = 0: North, i = 1: East, i = 2: South , i = 3: West, i = 4: Sprite
** i = 5: Ceiling, i = 6: Floor.
*/

void				exit_bonus(t_base *base, t_tex *tex_fc)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (tex_fc[i].xpm_img)
		{
			mlx_destroy_image(base->mlx.mlx, tex_fc[i].xpm_img);
			tex_fc[i].xpm_img = NULL;
		}
		i++;
	}
	exit_game(base, 1, 22); //
}

static void			load_floor_ceiling(t_base *base, t_tex *tex_fc, t_game *game, void *mlx)
{
	char	*path;
	int		i;

	i = 0;
	while (i < 2)
	{
		if (i == 0)
			path = "bonus/textures_xpm_floor_ceiling/Sand.xpm";
		else
			path = "bonus/textures_xpm_floor_ceiling/ice.xpm";
		tex_fc[i].xpm_img = mlx_xpm_file_to_image(mlx, path, &game->texwidth,
			&game->texheight);
		if (tex_fc[i].xpm_img == NULL)
			exit_bonus(base, tex_fc); //
		tex_fc[i].xpm_addr = mlx_get_data_addr(tex_fc[i].xpm_img, &tex_fc[i].xpm_bpp,
			&tex_fc[i].xpm_line_length, &tex_fc[i].xpm_endian);
		i++;
	}
}

void			floor_ceiling_texture(t_base *base)
{
	int 		y;
	t_tex		tex_fc[2]; //is een pointer
	t_floor		floor;

	load_floor_ceiling(base, tex_fc, &base->game, base->mlx.mlx);
	y = base->read.render_y / 2 + 1;
	while (y < base->read.render_y)
    {
		floor_ceiling_tex_y(&base->read, &base->game, &floor, y);
		floor_ceiling_tex_x_loop(base, &floor, tex_fc, y);
	  	y++;
    }
}
