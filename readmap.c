/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/10 13:38:27 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define TWOD base->read.array
#define READ base->read

/*
** Return (0) is succesful, Return (1) is failure
** TO DO: meer definen met READ
** TO DO: volg fout meldingen, leaks!, reorganise file.
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
	while (TWOD[*y][*i] >= '0' && TWOD[*y][*i] <= '9')
	{
		number = (number * 10) + TWOD[*y][*i] - '0';
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

int				check_save_resolution(int y, int i, t_base *base)
{
	i++;
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ' ) || TWOD[y][i] > '9')
		return (1);
	if (!(base->read.render_x == -1 || base->read.render_y == -1))
		return (1);
	base->read.render_x = cfr_itoa(&y, &i, base, 0);
	base->read.render_y = cfr_itoa(&y, &i, base, 0);
	if (base->read.render_x == -1 || base->read.render_y == -1)
		return (1);
	return (cfr_endspaces(y, i, base));
}

int				check_save_colors_cf(int y, int i, t_base *base)
{
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ') || TWOD[y][i] > '9')
		return (1);
	if (TWOD[y][i - 1] == 'C')
	{
		if (!(READ.c_red == -1 || READ.c_blue == -1 || READ.c_green == -1))
			return (1);						
		base->read.c_red = cfr_itoa(&y, &i, base, 0);
		base->read.c_blue = cfr_itoa(&y, &i, base, 1);
		base->read.c_green = cfr_itoa(&y, &i, base, 1);
		if (READ.c_red == -1 || READ.c_blue == -1 || READ.c_green == -1)
			return (1);
	}
	if (TWOD[y][i - 1] == 'F')
	{
		if (!(READ.f_red == -1 || READ.f_blue == -1 || READ.f_green == -1))
			return (1);
		base->read.f_red = cfr_itoa(&y, &i, base, 0);
		base->read.f_blue = cfr_itoa(&y, &i, base, 1);
		base->read.f_green = cfr_itoa(&y, &i, base, 1);
		if (READ.f_red == -1 || READ.f_blue == -1 || READ.f_green == -1)
			return (1);
	}
	return (cfr_endspaces(y, i, base));
}

int				check_pathstart(int y, int *i, t_base *base)
{
	while (TWOD[y][*i] == ' ')
		(*i)++;
	if (TWOD[y][*i] == '.' && TWOD[y][*i + 1] == '/')
		return (0);
	else
		return (1);
}

int				save_path_substr(int y, int i, char **identifier, t_base *base)//freeeeee
{
	if (*identifier != NULL)
		return (1);
	*identifier = ft_substr(TWOD[y], i, (ft_strlen(TWOD[y]) - i));
	if (*identifier == NULL)
		return (1);
	return (0);
}

/*
** i_entry is index when entering function. It's the index directly behind
** identifier.
*/
int				check_save_path(int y, int i, t_base *base)
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
		return (1);
	if (ret == 1)
		return (1);
	return (0);
}

// Check of map alleen bestaat uit 0, 1, 2, N,S,E or W
// Alle zijkanten 1
// No empty lines!
// Map als laatst
// Spaces are a valid part of the map, and is up to you to handle --> empty space?
// ook tabs vooraan de regel?

int			check_identifiers_valid(t_base *base)
{
	if (base->read.render_x > 0 && base->read.render_y > 0 &&
		(base->read.c_red >= 0 && base->read.c_red <= 255) &&
		(base->read.c_blue >= 0 && base->read.c_blue <= 255) &&
		(base->read.c_green >= 0 && base->read.c_green <= 255) &&
		(base->read.f_red >= 0 && base->read.f_red <= 255) &&
		(base->read.f_blue >= 0 && base->read.f_blue <= 255) &&
		(base->read.f_green >= 0 && base->read.f_green <= 255) &&
		base->read.no != NULL && base->read.ea != NULL && 
		base->read.so != NULL && base->read.we != NULL && 
		base->read.sprite != NULL)
		return (0);
	else
		return (1);
	
}

int			check_map(t_base *base) // int i, int y,
{
	if (check_identifiers_valid(base))
		return (1);
	// check of eerste regel uit spaties en 1 // save eerste 1
	// opvolgende regels beginnen met 1
		// 0, 1, 2, N,S,E or W
	//
	return (0);
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
		base->read.error = check_save_resolution(y, i, base);
	else if ((TWOD[y][i] == 'E' && TWOD[y][i + 1] == 'A') || (TWOD[y][i] == 'N'
	&& TWOD[y][i + 1] == 'O') || (TWOD[y][i] == 'W' && TWOD[y][i + 1] == 'E')
	|| (TWOD[y][i] == 'S' && (TWOD[y][i + 1] == 'O')))
		base->read.error = check_save_path(y, (i + 2), base);
	else if (TWOD[y][i] == 'S')
		base->read.error = check_save_path(y, (i + 1), base);
	else if (TWOD[y][i] == '1')
		base->read.error = check_map(base);
	else
		base->read.error = 1;
	if (base->read.error == 1)
		return (1);
	return (0);
}

/*
** base->read.error = 0 is default, 1 is error. Meaning the cub file is invalid
** Other values default -1. Because these numbers can be 0.
*/
void			initialise(t_base *base)
{
	base->read.error = 0;
	base->read.render_x = -1;
	base->read.render_y = -1;
	base->read.c_red = -1;
	base->read.c_blue = -1;
	base->read.c_green = -1;
	base->read.f_red = -1;
	base->read.f_blue = -1;
	base->read.f_green = -1;
	base->read.no = NULL;
	base->read.ea = NULL;
	base->read.so = NULL;
	base->read.we = NULL;
	base->read.sprite = NULL;
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

// t_base			*getcubfile(char *filename)
// {
// 	t_base	*new;
// 	char	*line;
// 	int		fd;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		printf("ERROR OPEN");
// 	line = ft_gnl_cub3d(fd);
// 	if (line == NULL)
// 		printf("ERROR GNL");
// 	new = (t_base *)malloc(sizeof(t_base));
// 	if (new == NULL)
// 		return (NULL);
// 	new->read.array = ft_split(line, '\n');
// 	free(line);
// 	return (new);
// }
