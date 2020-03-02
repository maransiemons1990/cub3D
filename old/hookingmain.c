/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hookingmain.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 18:33:53 by msiemons       #+#    #+#                */
/*   Updated: 2020/02/28 13:34:21 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

/*
keycode 53 is esc (apple). 
*/

int             close(int keycode, t_vars *vars)
{	
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
    	
	return (0);
}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    //mlx_key_hook(vars.win, close, &vars);
	mlx_hook(vars.win, 4, 1L<<2, close, &vars);
    mlx_loop(vars.mlx);
} 
// was: 2, 1L<<0
//(1L<<2) 04