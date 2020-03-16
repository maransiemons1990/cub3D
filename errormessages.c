/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errormessages.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:03:52 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/16 18:05:58 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		errormessages_10to13(t_base *base)
{
	if (base->read.error == 10)
		perror("Error\nInvalid character in the map");
	if (base->read.error == 11)
		perror("Error\nOnly 1 start position allowed in the map");
	if (base->read.error == 12)
		perror("Error\nInvalid outside wall");
	if (base->read.error == 13)
		perror("Error\nHole in the floor. Player may fall into black hole");
}

static void		errormessages_1to10(t_base *base)
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

void			error_distribution(t_base *base)
{
	if (base->read.error > 0 && base->read.error < 10)
		errormessages_1to10(base);
	if (base->read.error >= 10)
		errormessages_10to13(base);
}

void			error_general(int error)
{
	if (error == 1)
		perror("Error\nProgram expects two arguments\n");
	if (error == 2)
		perror("Error\nCan't open file\n");
	if (error == 3)
		perror("Error\nInvalid filetype\n");
	if (error == 4)
		perror("Error\nCan't GNL\n");
}