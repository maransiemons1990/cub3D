/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errormessages.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:03:52 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/01 12:29:05 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//perror als er een bestaande message is. 
// STDERR_FILENO write(STDOUT_FILENO, str, ft_strlen(str));

static void		errormessages_10up(t_base *base)
{
	char *str;
	
	str = NULL;
	if (base->read.error == 10)
		str = "Error\nInvalid character in the map\n";
	if (base->read.error == 11)
		perror("Error\nOnly 1 start position allowed in the map");
	if (base->read.error == 12)
		perror("Error\nInvalid outside wall");
	if (base->read.error == 13)
		perror("Error\nHole in the floor. Player may fall into black hole");
	if (base->read.error == 14)
		perror("Error\nMissing identifier(s) and/or map isn't at bottom file");
	if (base->read.error == 15)
		perror("Error\nNo player’s start position found.");
	if (base->read.error == 16)
		perror("Error\nMissing map");

	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
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

int				error_distribution(t_base *base)
{
	if (base->read.error > 0 && base->read.error < 10)
		errormessages_1to10(base);
	if (base->read.error >= 10 && base->read.error <= 19)
		errormessages_10up(base);
	end_free(base); //Voor read scene nog nodig!
	return (1);
}


static void		errormessages_20to(int	errornum)
{
	char *str;

	str = NULL;
	if (errornum == 20)
		str = "Error\nmlx failed to create a new window\n";
	if (errornum == 21)
		str = "Error\nfailed to create .xpm file path\n";
	if (errornum == 22)
		str = "Error\nmlx failed to create an image out of .xpm file\n";
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

void				error_distr(int errornum)
{
	// if (base->read.error > 0 && base->read.error < 10)
	// 	errormessages_1to10(base);
	// if (base->read.error >= 10 && base->read.error <= 19)
	// 	errormessages_10up(base);
	if (errornum >= 20)
		errormessages_20to(errornum);
		
	
	//end_free(base); Voor read scene nog nodig!
	//return (1);
}

void			*error_general(int error, char *line)
{
	if (error == 2)
		perror("Error\nInvalid file. Can only open existing .cub files\n");
	if (error == 3)
		perror("Error\nAn error occurred during processing input file\n");
	if (error == 4)
	{
		perror("Error\nAn error occurred during processing input file\n");
		free (line);
	}
	return (NULL);
}
