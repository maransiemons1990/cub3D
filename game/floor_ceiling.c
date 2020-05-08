/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 14:53:21 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/08 12:29:00 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** optional:
** color = (color >> 1) & 8355711; makes the floor or ceiling a bit darker.
*/

void				floor_ceiling_smooth(t_mlx *mlx, t_read *read)
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
			my_mlx_pixel_put(mlx, x, y, color);
        	color = read->c_color;
			my_mlx_pixel_put(mlx, x, (read->render_y - y - 1), color);
			x++;
      	}
	  y++;
    }
}
