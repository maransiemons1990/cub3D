/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/04 18:43:13 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
** Check of .cub file
*/

#include "cub3d.h"

int			main(int argc, char **argv)
{	
	t_base		*base;
	int y;

	y = 0;
	if (argc != 2)
	{
		printf("ERROR");
		return (1);
	}
	base = getcubfile(argv[1]);
	if (base == NULL)
		return (1);
	check(base);
	//------------------DELETE LATER------------------------------------
	twod_checker(base->read.array);
	return (0);
}