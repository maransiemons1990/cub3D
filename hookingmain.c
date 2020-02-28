/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hookingmain.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 18:33:53 by msiemons       #+#    #+#                */
/*   Updated: 2020/02/26 20:40:09 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

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
    	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    //mlx_key_hook(vars.win, close, &vars);
	mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    mlx_loop(vars.mlx);
} 