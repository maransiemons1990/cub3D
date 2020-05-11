/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 16:30:07 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/11 14:47:38 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Mlx_new_image: creates a new image in memory.
** The user can draw inside the image, and can dump the image inside a specified
** window. This is done using "mlx_put_image_to_window ()".
** Mlx_get_data_addr: returns information about the created image, allowing a
** user to modify it later. It returns a char * address that represents the
** beginning of the memory area where the image is stored. We should always
** calculate the memory offset using the line length set by mlx_get_data_addr.
** 		Img_ptr: specifies the image to use.
** 		Bits_per_pixel: the number of bits needed to represent a pixel color
** 		(also called the depth of the image).
** 		Size_line: the number of bytes used to store one line of the image
**		in memory. This information is needed to move from one line to another
** 		in the image.
** 		Endian: tells you wether the pixel color in the image needs to be
**		stored in little endian (== 0), or big endian (== 1) (byteorder).
*/

static int			loop(t_base *base)
{
	base->mlx.img = mlx_new_image(base->mlx.mlx, base->read.render_x,
		base->read.render_y);
	if (base->mlx.img == NULL)
		exit_game(base, 1, 26);
	base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bpp,
		&base->mlx.line_length, &base->mlx.endian);
	if (base->game.update)
		move_rotate(&base->game, &base->read, &base->move, base->read.array);
	floor_ceiling_smooth(&base->mlx, &base->read);
	raycasting(base, &base->game, &base->read);
	sprite(base, &base->sprite, &base->game, &base->read);
	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win,
		base->mlx.img, 0, 0);
	base->game.update = 0;
	return (0);
}

/*
** Mlx_init: This will establish a connection to the correct graphical system
** and returns the location of our current MLX instance/connection identifier.
** Mlx_new_window: creates a window and returns a pointer to it.
** Mlx_loop: to initiate the window rendering. It is an infinite loop that
** waits for an event. Each hook that was registered prior to this will be
** called accordingly by order of registration.
*/

int					game_mlx(t_base *base)
{
	initialise_game(&base->move, &base->mlx, base->tex, base);
	orientation(&base->game, base->read.pos);
	base->mlx.mlx = mlx_init();
	if (base->mlx.mlx == NULL)
		exit_game(base, 1, 29);
	base->mlx.mlx_win = mlx_new_window(base->mlx.mlx, base->read.render_x,
		base->read.render_y, "Wolfenstein 3D! | Maran Siemons");
	if (base->mlx.mlx_win == NULL)
		exit_game(base, 1, 20);
	load_texture(base, base->tex, &base->game, base->mlx.mlx);
	mlx_hook(base->mlx.mlx_win, 2, 1L << 0, &keypress, base);
	mlx_hook(base->mlx.mlx_win, 3, 1L << 1, &keyrelease, base);
	mlx_hook(base->mlx.mlx_win, 17, 1L << 17, &windowclose_x, base);
	if (base->save == 0)
	{
		loop(base);
		save_first_image_bmp(base);
		return (0);
	}
	mlx_loop_hook(base->mlx.mlx, &loop, base);
	mlx_loop(base->mlx.mlx);
	return (0);
}
