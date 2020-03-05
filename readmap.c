/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/05 16:15:00 by msiemons      ########   odam.nl         */
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

// return 0 is succesfull, 1 is failure
	//printf("number == [%d]\n", number);
	//	printf("in retun -1\n");
		//printf("i :[%d] = [%d]\n", i, TWOD[y][i]);
int				cfr_itoa(int *y, int *i, t_base *base, int cf_bg)
{
	int number;
	int nb_present;
	
	number = 0;
	nb_present = 0;
	while (TWOD[*y][*i] == ' ')
		(*i)++;
	if (cf_bg)
	{
		if (TWOD[*y][*i] == ',')
			(*i)++;
		else
			return (-1);
		while (TWOD[*y][*i] == ' ')
			(*i)++;
	}
	while (TWOD[*y][*i] >= '0' && TWOD[*y][*i] <='9')
	{
		number =  (number * 10) + TWOD[*y][*i] - '0';
		(*i)++;
		nb_present = 1;
	}
	return (nb_present == 1 ? number : -1);
 }

int				cfr_endspaces(int y, int i, t_base *base)
{
	while (TWOD[y][i])
	{
		if (TWOD[y][i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int			check_save_resolution(int y, int i, t_base *base)
{
	i++;
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ' ) || TWOD[y][i] >'9')
		return (1);
	base->read.render_x = cfr_itoa(&y, &i, base, 0);
	base->read.render_y = cfr_itoa(&y, &i, base, 0);
	if (base->read.render_x == -1|| base->read.render_y == -1)
		return (1);
	return (cfr_endspaces(y, i, base));
}

int				check_save_colors_cf(int y, int i, t_base *base)
{
	i++;
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ') || TWOD[y][i] >'9')
		return (1);
	if (TWOD[y][i - 1] == 'C')
	{
		base->read.c_red = cfr_itoa(&y, &i, base, 0);
		base->read.c_blue = cfr_itoa(&y, &i, base, 1);
		base->read.c_green = cfr_itoa(&y, &i, base, 1);
		if (base->read.c_red == -1 || base->read.c_blue == -1 || base->read.c_green == -1)
			return (1);
	}
	if (TWOD[y][i - 1] == 'F')
	{
		base->read.f_red = cfr_itoa(&y, &i, base, 0);
		base->read.f_blue = cfr_itoa(&y, &i, base, 1);
		base->read.f_green = cfr_itoa(&y, &i, base, 1);
		if (base->read.f_red == -1 || base->read.f_blue == -1 || base->read.f_green == -1)
			return (1);
	}
	return (cfr_endspaces(y, i, base));
}

// int			chech_save_path(int y, int i, t_base *base)
// {
	
// }

		//printf("--Ga naar functie CF--[%s]\n", TWOD[y]);
static int			check_line(int y, t_base *base)
{
	int		i;

	i = 0;
	while (TWOD[y][i] == ' ')
		i++;
	if (TWOD[y][i] == 'C' || TWOD[y][i] == 'F')
		base->read.error = check_save_colors_cf(y, i, base);
	else if (TWOD[y][i] == 'R')
		base->read.error = check_save_resolution(y, i, base);
	else if ((TWOD[y][i] == 'E' && TWOD[y][i + 1] == 'A') || (TWOD[y][i] == 'N'
			&& TWOD[y][i + 1] == 'O') || (TWOD[y][i] == 'W'
			&& TWOD[y][i + 1] == 'E') || (TWOD[y][i] == 'S'
			&& (TWOD[y][i + 1] == 'O' || TWOD[y][i + 1] == ' ')))
		//base->read.error = check_save_path(y, i, base);
		printf("--Ga naar functie path--[%s]\n", TWOD[y]);
	else if (TWOD[y][i] == '1')
		printf("--Het is een 1--[%s]\n", TWOD[y]);
	else
		base->read.error = 1;
	if (base->read.error == 1)
		return (1);
	return (0);
}

void			initialise(t_base *base)
{
	base->read.error = 0; // 1 is error, 0 is goed //Invalid cub
	base->read.render_x = -1; //alle values default op -1 want getal kan ook 0 zijn.
	base->read.render_y = -1;
	base->read.c_red = -1;
	base->read.c_blue = -1;
	base->read.c_green = -1;
	base->read.f_red = -1;
	base->read.f_blue = -1;
	base->read.f_green = -1;
	// base->read.no = -1;
	// base->read.ea = -1;
	// base->read.so = -1;
	// base->read.we = -1;
	// base->read.sprite = -1;
}

int			check(t_base *base)
{
	int		y;
	int		line;

	y = 0;
	
	initialise(base);
	while (base->read.array[y])
	{
		line = check_line(y, base);
		if (line == 1)
			return (1);
		y++;
	}
	return (0);
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
