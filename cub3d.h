/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:30:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/02/28 17:47:00 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

//Delete?:
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_data {
    void		*mlx;
	void    	*mlx_win;

	void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//Tutorial:
void		print_triangle(t_data *img, int x, int y, int radius);
void		print_full_square(t_data *img, int x, int xsize, int y, int ysize);
void		print_square(t_data *img, int x, int xsize, int y, int ysize);

#endif