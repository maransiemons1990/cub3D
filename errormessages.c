/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errormessages.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:03:52 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/11 12:50:45 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	errormessages(t_base *base)
{
	if (base->read.error == 1)
		perror("Error\nInvalid inputfile");
	if (base->read.error == 2)
		perror("Error\nInvalid character(s)");
	if (base->read.error == 3)
		perror("Error\nSeveral identical identifiers");
	if (base->read.error == 4)
		perror("Error\nInvalid format of identifier(s)");

	if (base->read.error == 5)
	 	perror("Error\nInvalid path(s)");
	if (base->read.error == 6)
	 	perror("Error\nMalloc failed");

	if (base->read.error == 7)
	 	perror("Error\nResolution can't be 0");
	if (base->read.error == 8)
	 	perror("Error\nColor values should be between 0 - 255");
	if (base->read.error == 9)
	 	perror("Error\nThe path(s) could not be accessed");
}

