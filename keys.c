/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 17:27:15 by Maran          #+#    #+#                */
/*   Updated: 2020/03/25 18:41:41 by Maran         ########   odam.nl         */
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
	if (keycode == KEY_LEFT)
		base->game.x = 1;
	if (keycode == KEY_RIGHT)
		base->game.y = 1;
    return (0);
}

int			windowclose_x(t_base *img)
{	
	(void)img;
	exit (0);
}
