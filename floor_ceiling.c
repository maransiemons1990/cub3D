/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 14:53:21 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/06 18:30:08 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			floor_ceiling_smooth(t_base *base, t_read *read)
{
	int 	y;
	int 	x;
	int 	color;

	y = read->render_y / 2 + 1;
	while (y < read->render_y)
    {
		x = 0;
		while (x < read->render_x)
      	{
			color = read->f_color;
        	//color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(&base->mlx, x, y, color);
        	color = read->c_color;
        	//color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(&base->mlx, x, (read->render_y - y - 1), color);
			x++;
      	}
	  y++;
    }
}
