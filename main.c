/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:30:15 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/05 13:22:58 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* 
** Check of .cub file
*/

#include "cub3d.h"

int			main(int argc, char **argv)
{	
	t_base		*base;
	int			ret;
	int y;

	y = 0;
	if (argc != 2)
	{
		printf("EXPECTS TWO ARGUMENTS");
		return (1);
	}
	base = getcubfile(argv[1]);
	if (base == NULL)
		return (1);
	ret = check(base);
	if (ret == 1)
	{
		errormessages(base);
		return (1);
	}
		
	
	
	//------------------DELETE LATER------------------------------------
	valuechecker(base);
	//twod_checker(base->read.array);
	return (0);
}