/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons      #+#    #+#                 */
/*   Updated: 2020/04/28 22:22:24 by Maran         ########   odam.nl         */
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
	int			ret;

	if (argc != 2 && argc != 3)
	{
		perror("Error\nProgram expects one argument\n");
		return (1);
	}
	base = getcubfile(argv[1]);
	if (base == NULL)
		return (1);
	if (argc == 3)
	{
		base->save = (ft_strcmp(argv[2], "--save"));
		if (base->save)
			return (printf("Error\nDid you mean option --save as 2nd argument?\n"));
	}
	ret = read_scene_file(base);
	if (ret > 0)
		return (error_distribution(base));
	displayresolution(base);
	//------------------DELETE LATER------------------------------------
	//printf("----after---\n");
	//print_list(base);
	//base->head = insertion_sort(base->head);
	//sort(base);
	//valuechecker(base);
	//twod_checker(base->read.array);
	//------------------------------------------------------------------
	mlx(base);
	//------------------------------------------------------------------
	end_free(base);
	return (0);
}