/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/06 14:34:11 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Other option I could have used:
** mlx_get_screen_size(base->mlx.mlx, &base->read.render_x, &base->read.render_y);
*/

void			displayresolution(t_base *base)
{
	int		maindisplayid;
	int		pixelswidth;
	int		pixelsheight;
	
	maindisplayid = CGMainDisplayID();
    pixelswidth = CGDisplayPixelsWide(maindisplayid);
    pixelsheight = CGDisplayPixelsHigh(maindisplayid);
	if (base->read.render_x > pixelswidth)
		base->read.render_x = pixelswidth;
	if (base->read.render_y > pixelsheight)
		base->read.render_y = pixelsheight;
}


/*
** Option: --save to make a screenshot of the first image and save as bmp
*/

int			main(int argc, char **argv)
{	
	t_base		*base;

	if (argc != 2 && argc != 3)
		return (error_distr(NULL, 30));
	base = getcubfile(argv[1]);
	if (argc == 3)
	{
		base->save = (ft_strcmp(argv[2], "--save"));
		if (base->save)
			return (error_distr(base, 31));
	}
	read_scene_file(base, &base->read);
	displayresolution(base);
	mlx(base);
	return (0);
}