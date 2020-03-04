/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   twod_checker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:18:26 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/04 18:29:13 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		twod_checker(char **array)
{
	int 	y;

	y = 0;
	while(array[y])
	{
		printf("array[%i]: [%s]\n", y, array[y]);
		y++;
	}
}
