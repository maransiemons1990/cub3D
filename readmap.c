/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/11 12:47:38 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Return (0) is succesful, Return (1) is failure
** TO DO: meer definen met READ
** TO DO: volg fout meldingen, leaks!, reorganise file.
** TO DO:checken of bestanden kunnen openen.
** TRGB INBOUWEN/ OPEN CHECK VRAGEN AAN MEREL
*/

/*
** each type of element can be separated by one or more empty line(s).
** each type of element can be set in any order in the file.
** each type of information from an element can be separated by one or more space(s).
** Each element of the map must be separated by exactly one space. Spaces are valid elements of the map,
** meaning there is nothing, and are up to you to handle.
** Each element firsts information is the type identifier (composed by one or two character(s)),
** followed by all specific informations for each object in a strict order such as :
*/

/*
** i_entry is index when entering function. It's the index directly behind
** identifier.
*/

static int		check_save_path(int y, int i, t_base *base)
{
	int i_entry;
	int ret;

	ret = 0;
	i_entry = i;
	if ((check_pathstart(y, &i, base)) == 0)
	{
		if (TWOD[y][i_entry - 2] == 'N' && TWOD[y][i_entry - 1] == 'O')
			ret = save_path_substr(y, i, &base->read.no, base);
		else if (TWOD[y][i_entry - 2] == 'E' && TWOD[y][i_entry - 1] == 'A')
			ret = save_path_substr(y, i, &base->read.ea, base);
		else if (TWOD[y][i_entry - 2] == 'W' && TWOD[y][i_entry - 1] == 'E')
			ret = save_path_substr(y, i, &base->read.we, base);
		else if (TWOD[y][i_entry - 2] == 'S' && TWOD[y][i_entry - 1] == 'O')
			ret = save_path_substr(y, i, &base->read.so, base);
		else if (TWOD[y][i_entry - 1] == 'S')
			ret = save_path_substr(y, i, &base->read.sprite, base);
	}
	else
		return (5); // #5
	if (ret == 3 || ret == 6)
		return (ret == 3 ? 3 : 6); //#3 #6
	if (ret == 9)
		return (9); //#9
	return (0);
}

static int		check_save_resolution(int y, int i, t_base *base)
{
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ') || TWOD[y][i] > '9')
		return (2); // #2
	if (!(base->read.render_x == -1 || base->read.render_y == -1))
		return (3); // #3
	base->read.render_x = cfr_itoa(&y, &i, base, 0);
	base->read.render_y = cfr_itoa(&y, &i, base, 0);
	if (base->read.render_x == -1 || base->read.render_y == -1)
		return (4); // #4
	if (base->read.render_x <= 0 || base->read.render_y <=0)
		return (7); //#7
	return (cfr_endspaces_resetrgb(y, i, base));
}

static int		check_save_colors_cf(int y, int i, t_base *base)
{
	int entry_i;
	int	ret;
	
	entry_i = i - 1;
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ') || TWOD[y][i] > '9')
		return (2); //Invalid character #2
	base->read.red = cfr_itoa(&y, &i, base, 0);
	base->read.blue = cfr_itoa(&y, &i, base, 1);
	base->read.green = cfr_itoa(&y, &i, base, 1);
	if (READ.red == -1 || READ.blue == -1 || READ.green == -1)
		return (4); //Invalid identifier format # 4
	if (!(READ.red >= 0 &&  READ.red <= 255) && (READ.blue >= 0 &&
	READ.blue <= 255) && (READ.green >= 0 &&  READ.green <= 255))
		return (8); // #8
	ret = create_trgb_colorcode(y, entry_i, base);
	if (ret == 3)
		return (3); //#3
	return (cfr_endspaces_resetrgb(y, i, base));
}

static int		check_line(int y, t_base *base)
{
	int		i;

	i = 0;
	while (TWOD[y][i] == ' ' || TWOD[y][i] == '\t')
		i++;
	if (TWOD[y][i] == 'C' || TWOD[y][i] == 'F')
		base->read.error = check_save_colors_cf(y, (i + 1), base);
	else if (TWOD[y][i] == 'R')
		base->read.error = check_save_resolution(y, (i + 1), base);
	else if ((TWOD[y][i] == 'E' && TWOD[y][i + 1] == 'A') || (TWOD[y][i] == 'N'
	&& TWOD[y][i + 1] == 'O') || (TWOD[y][i] == 'W' && TWOD[y][i + 1] == 'E')
	|| (TWOD[y][i] == 'S' && (TWOD[y][i + 1] == 'O')))
		base->read.error = check_save_path(y, (i + 2), base);
	else if (TWOD[y][i] == 'S')
		base->read.error = check_save_path(y, (i + 1), base);
	else if (TWOD[y][i] == '1')
		//base->read.error = check_map(base);
		printf("--Het is een 1--\n");
	else
		base->read.error = 1; //invalid input file #1
	if (base->read.error > 0)
		return (1);
	return (0);
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
