/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/17 17:30:19 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
** Check of .cub file
**
** Return (0) is succesful, Return (1) is failure.
** TO DO: meer definen met READ?
** TO DO: leaks!, reorganise file.
** TO DO: GNL etc fix.
*/

#include "cub3d.h"

int			main(int argc, char **argv)
{	
	t_base		*base;
	int			ret;

	if (argc != 2)
	{
		perror("Error\nProgram expects one argument\n");
		return (1);
	}
	base = getcubfile(argv[1]);
	if (base == NULL)
		return (1);
	ret = read_scene_file(base);
	if (ret > 0)
		return (error_distribution(base));
	//------------------DELETE LATER------------------------------------
	valuechecker(base);
	//twod_checker(base->read.array);
	//------------------------------------------------------------------
	end_free(base);
	return (0);
}