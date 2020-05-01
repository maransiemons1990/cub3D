/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errormessages.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:03:52 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/01 19:07:01 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//perror als er een bestaande message is. 
// STDERR_FILENO write(STDOUT_FILENO, str, ft_strlen(str));



// int				error_distribution(t_base *base)
// {
// 	if (base->read.error > 0 && base->read.error < 10)
// 		errormessages_1to10(base);
// 	if (base->read.error >= 10 && base->read.error <= 19)
// 		errormessages_10up(base);
// 	end_free(base); //Voor read scene nog nodig!
// 	return (1);
// }



static void		errormessages_30to(t_base *base, int errornum)
{
	char *str;

	str = NULL;
	if (errornum == 30)
		str = "Error\nProgram expects one argument\n";
	if (errornum == 31)
	{
		str = "Error\nDid you mean option --save as 2nd argument?\n";
		free_array(&base->read);
		free(base);
	}
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

static void		errormessages_20to(int	errornum)
{
	char *str;

	str = NULL;
	if (errornum == 20)
		str = "Error\nMlx failed to create a new window\n";
	if (errornum == 21)
		str = "Error\nFailed to create .xpm file path\n";
	if (errornum == 22)
		str = "Error\nMlx failed to create an image out of .xpm file\n";
	if (errornum == 23)
		perror("Error\nFailed to open/create .bmp file --save");
	if (errornum == 24)
		perror("Error\nFailed to allocate memory for bitmap --save");
	if (errornum == 25)
		perror("Error\nFailed to write into bitmap file");
	if (errornum == 26)
		str = "Error\nMlx failed to create an image\n";
	if (errornum == 27)
		perror("Error\nFailed to allocate memory for Zbuffer");
	if (errornum == 28)
		str = "Error\nThe used processor time couldn't be established\n";
	if (errornum == 29)
		str = "Error\nMlx failed to set up the connection to the display\n";
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

static void		errormessages_10up(int errornum)
{
	char *str;
	
	str = NULL;
	if (errornum == 10)
		str = "Error\nInvalid character in the map\n";
	if (errornum == 11)
		perror("Error\nOnly 1 start position allowed in the map");
	if (errornum == 12)
		perror("Error\nInvalid outside wall");
	if (errornum == 13)
		perror("Error\nHole in the floor. Player may fall into black hole");
	if (errornum == 14)
		perror("Error\nMissing identifier(s) and/or map isn't at bottom file");
	if (errornum == 15)
		perror("Error\nNo player’s start position found.");
	if (errornum == 16)
		perror("Error\nMissing map");

	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

static void		errormessages_1to10(int errornum)
{
	char *str;

	str = NULL;
	if (errornum == 1)
		perror("Error\nInvalid inputfile");
	if (errornum == 2)
		str = "Error\nInvalid character(s)";
	if (errornum == 3)
		perror("Error\nSeveral identical identifiers");
	if (errornum == 4)
		perror("Error\nInvalid format of identifier(s)");
	if (errornum == 5)
	 	perror("Error\nInvalid path(s)");
	if (errornum == 6)
	 	perror("Error\nMalloc failed");
	if (errornum == 7)
	 	perror("Error\nResolution can't be 0");
	if (errornum == 8)
	 	perror("Error\nColor values should be between 0 - 255");
	if (errornum == 9)
	 	perror("Error\nThe path(s) could not be accessed");
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

void			*error_gnl_cub(int error, char *line)
{
	if (error == 2)
		perror("Error\nFailed to open .cub scenefile\n");
	if (error == 3)
		perror("Error\nAn error occurred during processing input file\n");
	if (error == 4)
	{
		perror("Error\nAn error occurred during processing input file\n");
		free (line);
	}
	return (NULL);
}

// return 1 to functions means error has happened
int				error_distr(t_base *base, int errornum)
{
	if (errornum >= 1 && errornum <= 9)
		errormessages_1to10(errornum);
	if (errornum >= 10 && errornum <= 19)
		errormessages_10up(errornum);
	if (errornum >= 20 && errornum <= 29)
		errormessages_20to(errornum);
	if (errornum >= 1 && errornum <= 29)
		free_cub_base(base);
	if (errornum >= 30)
	 	errormessages_30to(base, errornum);
	return (1);
}
