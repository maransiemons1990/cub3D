/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_mlx.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 16:30:07 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/08 12:25:28 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** 
** img_ptr - specifies the image to use. 
** bits_per_pixel - the number of bits needed to represent a pixel color
** (also called the depth of the image).
** size_line - the number of bytes used to store one line of the image in memory.
** This information is needed to move from one line to another in the image.
** endian - tells you wether the pixel color in the image needs to be stored in
** little endian (== 0), or big endian (== 1).
*/
static int			loop(t_base *base)
{
	base->mlx.img = mlx_new_image(base->mlx.mlx, base->read.render_x, base->read.render_y);
	if (base->mlx.img == NULL)
		exit_game(base, 1, 26);
	base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bpp, &base->mlx.line_length, &base->mlx.endian);
	if (base->game.update)
		move_rotate(&base->game, &base->read, base->read.array);
	floor_ceiling_smooth(&base->mlx, &base->read);
	raycasting(base, &base->game, &base->read);
	sprite(base, &base->sprite, &base->game, &base->read);
	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
	base->game.update = 0;
	return (0);
}

/*
** mlx_init: This will establish a connection to the correct graphical system
** and will return a void * which holds the location of our current MLX instance/ connection identifier.
** mlx_new_window: creating a window. Return a pointer to the window we have just created.
** mlx_loop: to initiate the window rendering. It is an infinite loop that waits for
** an event, and then calls a user-defined function associated with this event.
** Loop over the given mlx pointer. Each hook that was registered prior to this will be called accordingly by order of registration.
** mlx_new_image creates a new image in memory.
** The user can draw inside the image, and can dump the image inside a specified window
** at any  time  to  display  it  on  the screen. This is done using **mlx_put_image_to_window ()**.
** mlx_get_data_addr: returns information about the created image, allowing a user to modify it later.
** returns a char * address that represents the begining of the memory area where the image is stored.
** We should ALWAYS calculate the memory offset using the line length set by mlx_get_data_addr.
** TO DO: temporary image aanmaken.
** X11_EVENT_KEY_PRESS 2, X11_EVENT_KEY_RELEASE 3, X11_EVENT_EXIT 17
*/
int					game_mlx(t_base *base)
{
	initialise_game(&base->game, &base->mlx, base->tex, base->zbuffer);
	orientation(&base->game, base->read.pos);
	base->mlx.mlx = mlx_init();
	if (base->mlx.mlx == NULL)
		exit_game(base, 1, 29);
	base->mlx.mlx_win = mlx_new_window(base->mlx.mlx, base->read.render_x,
		base->read.render_y, "Wolfenstein 3D! | Maran Siemons");
	if (base->mlx.mlx_win == NULL)
		exit_game(base, 1, 20);
	load_texture(base, base->tex, &base->game, base->mlx.mlx);
	mlx_hook(base->mlx.mlx_win, 2, 1L<<0, &keypress, base);
	mlx_hook(base->mlx.mlx_win, 3, 1L<<1, &keyrelease, base);
	mlx_hook(base->mlx.mlx_win, 17, 1L<<17, &windowclose_x, base);
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
