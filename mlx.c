/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 16:30:07 by Maran          #+#    #+#                */
/*   Updated: 2020/03/31 10:21:54 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//initial direction vector
void			orientation(t_base *base)
{
	base->game.dirX = 0; 
	base->game.dirY = 0; 
	if (base->read.pos == 'N')
		base->game.dirY = -1;
	if (base->read.pos == 'S')
		base->game.dirY = 1;
	if (base->read.pos == 'E')
		base->game.dirX = 1;	
	if (base->read.pos == 'W')
		base->game.dirX = -1;
}

/*
** mlx_init: This will establish a connection to the correct graphical system
** and will return a void * which holds the location of our current MLX instance/ connection identifier.
** mlx_new_window: creating a window. Return a pointer to the window we have just created.
** mlx_loop: to initiate the window rendering. It is an infinite loop that waits for
** an event, and then calls a user-defined function associated with this event
** mlx_new_image creates a new image in memory.
** The user can draw inside the image, and can dump the image inside a specified window
** at any  time  to  display  it  on  the screen. This is done using **mlx_put_image_to_window ()**.
** mlx_get_data_addr: returns information about the created image, allowing a user to modify it later.
** returns a char * address that represents the begining of the memory area where the image is stored.
** We should ALWAYS calculate the memory offset using the line length set by mlx_get_data_addr.
** TO DO: temporary image aanmaken. 
*/

int				mlx(t_base *base)
{
	orientation(base);
	base->mlx.mlx = mlx_init();
	base->mlx.mlx_win = mlx_new_window(base->mlx.mlx, base->read.render_x, base->read.render_y, "Hello world!");
	//base->mlx.img = mlx_new_image(base->mlx.mlx, base->read.render_x, base->read.render_y);
	//base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bits_per_pixel, &base->mlx.line_length, &base->mlx.endian);

// /* ----------HOOKING EVENT-----------------*/ 
	mlx_hook(base->mlx.mlx_win, X11_EVENT_KEY_PRESS, 1L<<0, &keypress, base);				//wel of geen & voor functie? // geen & voor base!
	//mlx_hook(base->mlx.mlx_win, X11_EVENT_KEY_RELEASE, 1L<<1, &keyrelease, &base);
	mlx_hook(base->mlx.mlx_win, X11_EVENT_EXIT, 1L<<17, &windowclose_x, base);
	//loop(base);
	mlx_loop_hook(base->mlx.mlx, &loop, base);
	
// // /*----------------------------------------------*/
 	mlx_loop(base->mlx.mlx);
	//mlx_destroy_image(base->mlx.mlx, base->mlx.new_img);
	return (0);
}
