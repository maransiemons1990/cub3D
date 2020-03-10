/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errormessages.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:03:52 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/10 16:55:30 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	errormessages(t_base *base)
{
	if (base->read.error == 1)
		perror("Error\nInvalid input file ");
	if (base->read.error == 2)
		perror("Error\nInvalid character, 
		first information has to be the type identifier");	
}
