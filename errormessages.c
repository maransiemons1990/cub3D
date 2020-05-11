/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errormessages.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 13:03:52 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/11 14:39:17 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Use of perror when there is an existing system error message available.
** Otherwise a manual error message is written to the standard error output.
*/

static void			errormessages_30to(t_base *base, int errornum)
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
	if (errornum == 32)
		perror("Error\nFailed to open .cub scenefile\n");
	if (errornum == 33)
		str = "Error\nAn error occurred during processing input file\n";
	if (errornum == 34)
		perror("Error\nFailed to allocate memory for struct");
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

static void			errormessages_20to(int errornum)
{
	char	*str;

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

static void			errormessages_10up(int errornum)
{
	char	*str;

	str = NULL;
	if (errornum == 10)
		str = "Error\nInvalid character in the map\n";
	if (errornum == 11)
		str = "Error\nOnly 1 start position allowed in the map\n";
	if (errornum == 12)
		str = "Error\nInvalid outside wall\n";
	if (errornum == 13)
		str = "Error\nHole in the floor. Player may fall into black hole\n";
	if (errornum == 14)
		str = "Error\nMissing identifier(s) and/or map isn't at bottom file\n";
	if (errornum == 15)
		str = "Error\nNo player’s start position found\n";
	if (errornum == 16)
		str = "Error\nMissing map\n";
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

static void			errormessages_1to10(int errornum)
{
	char	*str;

	str = NULL;
	if (errornum == 1)
		str = "Error\nInvalid inputfile\n";
	if (errornum == 2)
		str = "Error\nInvalid character(s)\n";
	if (errornum == 3)
		str = "Error\nSeveral identical identifiers\n";
	if (errornum == 4)
		str = "Error\nInvalid format of identifier(s)";
	if (errornum == 5)
		str = "Error\nInvalid path(s)\n";
	if (errornum == 6)
		perror("Error\nMalloc failed");
	if (errornum == 7)
		str = "Error\nResolution can't be 0";
	if (errornum == 8)
		str = "Error\nColor values should be between 0 - 255\n";
	if (errornum == 9)
		perror("Error\nThe path(s) could not be accessed");
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
}

/*
** Main and gnl_cub errors (errornum >= 30) are treated different because
** depending on the location there may or may not be allocated memory yet.
** So we don't have to free in every case.
*/

int					error_distr(t_base *base, int errornum)
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
	exit(1);
	return (1);
}
