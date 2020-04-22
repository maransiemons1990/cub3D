/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons      #+#    #+#                 */
/*   Updated: 2020/04/22 16:21:58 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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