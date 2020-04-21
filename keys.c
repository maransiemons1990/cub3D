/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 17:27:15 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/17 11:43:48 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Segfault met destroy window. Uitzoeken.
int             keypress(int keycode, t_base *base)
{
	if (keycode == KEY_ESC)
	{
		(void)base;
		//mlx_destroy_window(img->mlx.mlx, img->mlx.mlx_win);
		exit (0);
	}
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_D ||
	keycode == KEY_A || keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		base->game.update = 1;
		if (keycode == KEY_W)
			base->game.move_front = 1;
		if (keycode == KEY_S)
			base->game.move_back = 1;
		if (keycode == KEY_D)
			base->game.move_right = 1;
		if (keycode == KEY_A)
			base->game.move_left = 1;
		if (keycode == KEY_LEFT)
			base->game.rotate_left = 1;
		if (keycode == KEY_RIGHT)
			base->game.rotate_right = 1;
	}
    return (0);
}

int             keyrelease(int keycode, t_base *base)
{	
	if (keycode == KEY_W)
		base->game.move_front = 0;
	if (keycode == KEY_S)
		base->game.move_back = 0;
	if (keycode == KEY_D)
		base->game.move_right = 0;
	if (keycode == KEY_A)
		base->game.move_left = 0;
	if (keycode == KEY_LEFT)
		base->game.rotate_left = 0;
	if (keycode == KEY_RIGHT)
		base->game.rotate_right = 0;
    return (0);
}

int			windowclose_x(t_base *img)
{	
	(void)img;
	exit (0);
}

// int			resize_window(t_base *img)
// {	
// 	(void)img;
// 	exit (0);
// }