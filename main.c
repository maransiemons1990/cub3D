/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/24 18:20:41 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


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
	mlx(base);
	//------------------------------------------------------------------
	end_free(base);
	return (0);
}