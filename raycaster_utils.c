/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 18:32:30 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/06 20:46:43 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Pushing pixels to the window. we will have to buffer all of our pixels to a image
** which we will then push to the window.
** Instead of push the pixel instantly to the window (without waiting for the frame to be entirely rendered).
** Locate postion of pixel: (y * size_line + x * (bits_per_pixel / 8));
** Here we multiply size_line by y as we need to skip y lines (line size does not equal the amount of pixels in a line).
** We then add the remaining x units multiplied by bits_per_pixl / 8 to align with the final location.
*/

void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char    *dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
	*(unsigned int*)dst = color;
}


