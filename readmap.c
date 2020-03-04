/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/04 19:34:10 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define TWOD base->read.array

/*
** each type of element can be separated by one or more empty line(s).
** each type of element can be set in any order in the file.
** each type of information from an element can be separated by one or more space(s).
** Each element of the map must be separated by exactly one space. Spaces are valid elements of the map,
** meaning there is nothing, and are up to you to handle.
** Each element firsts information is the type identifier (composed by one or two character(s)),
** followed by all specific informations for each object in a strict order such as :
*/

	//R 1920 1080

int			check_save_r(int y, int i, t_base *base)
{
	i++;
	if ((TWOD[y][i] >= '0' && TWOD[y][i] <='9') || TWOD[y][i] == ' ')
		return (0);
	while (TWOD[y][i] == ' ')
		i++;
	while (TWOD[y][i] >= '0' && TWOD[y][i] <='9')
	{
		base->read.render_x =  (base->read.render_x* 10) + TWOD[y][i] - '0';
		i++;
	}
	
}

static int			check_line(int y, t_base *base)
{
	int		i;

	i = 0;
	while (TWOD[y][i] == ' ')
		i++;
	if (TWOD[y][i] == 'C' || TWOD[y][i] == 'F')
		printf("--Ga naar functie CF--[%s]\n", TWOD[y]);
	else if (TWOD[y][i] == 'R')
		printf("--Ga naar functie R--[%s]\n", TWOD[y]);
	else if ((TWOD[y][i] == 'E' && TWOD[y][i + 1] == 'A') || (TWOD[y][i] == 'N'
			&& TWOD[y][i + 1] == 'O') || (TWOD[y][i] == 'W'
			&& TWOD[y][i + 1] == 'E') || (TWOD[y][i] == 'S'
			&& (TWOD[y][i + 1] == 'O' || TWOD[y][i + 1] == ' ')))
		printf("--Ga naar functie path--[%s]\n", TWOD[y]);
	else if (TWOD[y][i] == '1')
		printf("--Het is een 1--[%s]\n", TWOD[y]);
	else
		return (0);
	return (1);
}

void			check(t_base *base)
{
	int		y;
	int		line;

	y = 0;
	base->read.error = 0;
	while (base->read.array[y])
	{
		line = ft_check_line(y, base);
		if (line == 0)
		{
			printf("FOUTE IDENTIFIER\n");
			exit;
		}
		y++;
	}
}

t_base			*getcubfile(char *filename)
{
	t_base	*new;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		printf("ERROR OPEN");
	line = ft_gnl_cub3d(fd);
	if (line == NULL)
		printf("ERROR GNL");
	new = (t_base *)malloc(sizeof(t_base));
	if (new == NULL)
		return (NULL);
	new->read.array = ft_split(line, '\n');
	free(line);
	return (new);
}
