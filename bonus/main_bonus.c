/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/13 13:09:28 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"
# include <CoreGraphics/CGDirectDisplay.h>


static void			display_resolution(int *render_x, int *render_y)
{
	int		maindisplayid;
	int		pixelswidth;
	int		pixelsheight;

	maindisplayid = CGMainDisplayID();
	pixelswidth = CGDisplayPixelsWide(maindisplayid);
	pixelsheight = CGDisplayPixelsHigh(maindisplayid);
	if (*render_x > pixelswidth)
		*render_x = pixelswidth;
	if (*render_y > pixelsheight)
		*render_y = pixelsheight;
}

/*
** Option: --save to make a screenshot of the first image and save as bmp
*/

int					main(int argc, char **argv)
{
	t_base	*base;

	if (argc != 2 && argc != 3)
		return (error_distr(NULL, 30));
	base = get_cub_file(argv[1]);
	if (argc == 3)
	{
		base->save = (ft_strcmp(argv[2], "--save"));
		if (base->save)
			return (error_distr(base, 31));
	}
	read_scene_file(base, &base->read);
	display_resolution(&base->read.render_x, &base->read.render_y);
	game_mlx_bonus(base);
	return (0);
}
