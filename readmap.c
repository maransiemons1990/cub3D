/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/05 18:50:25 by msiemons      ########   odam.nl         */
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







//N O   . /
//0 1 2 3 4 5
//    i 
//      i  
// i - 2 - (inew - ioud)
// 5 - 2 - (5 - 2)



int			check_pathstart(int y, int *i, t_base *base)
{
	while (TWOD[y][*i] == ' ')
		(*i)++;
	if (TWOD[y][*i] == '.' && TWOD[y][*i + 1] == '/')
		return (0);
	else
		return (1);
}

int			save_path_substr(int y, int i, char **identifier, t_base *base)//freeeeee
{
	*identifier = ft_substr(TWOD[y], i, (ft_strlen(TWOD[y]) - i));
	if (*identifier == NULL)
		return (1);
	return (0);
}

int			check_save_path(int y, int i, t_base *base) 
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



// int			check_save_path_cardinal(int y, int i, t_base *base) //freeeeee
// {
// 	int i_entry;

// 	i_entry = i;
// 	if ((check_pathstart(y, &i, base)) == 0)
// 	{
// 		if (TWOD[y][i - i_entry] == 'N' && TWOD[y][i_entry - 1] == 'O')
// 			base->read.no = ft_substr(TWOD[y], i, ft_strlen(TWOD[y]) - i);
// 			if base->read.no == NULL
// 				return (1);
// 		if (TWOD[y][i - i_entry] == 'E' && TWOD[y][i_entry - 1] == 'A')
// 			base->read.ea = ft_substr(TWOD[y], i, ft_strlen(TWOD[y]) - i);
// 			if base->read.ea == NULL
// 				return (1);
// 		if (TWOD[y][i - i_entry] == 'S' && TWOD[y][i_entry - 1] == 'O')
// 			base->read.so = ft_substr(TWOD[y], i, ft_strlen(TWOD[y]) - i);
// 			if base->read.so == NULL
// 				return (1);
// 		if (TWOD[y][i - i_entry] == 'W' && TWOD[y][i_entry - 1] == 'E')
// 			base->read.we = ft_substr(TWOD[y], i, ft_strlen(TWOD[y]) - i);
// 			if base->read.we == NULL
// 				return (1);
// 	}
// 	else
// 		return (1);
// 	return (0);
// }

// int		check_save_path_sprite(int y, int i, t_base *base) //freeeeee
// {
// 	int i_entry;

// 	i_entry = i;
// 	if ((check_pathstart(y, &i, base)) == 0)
// 	{
// 		base->read.sprite = ft_substr(TWOD[y], i, ft_strlen(TWOD[y]) - i);
// 		if base->read.sprite == NULL
// 			return (1);
// 	}
// }




// || (TWOD[y][i + 1] == ' ' || TWOD[y][i + 1] == '.')))
		//printf("--Ga naar functie path--[%s]\n", TWOD[y]);
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
		&& TWOD[y][i + 1] == 'O') || (TWOD[y][i] == 'W' && 
		TWOD[y][i + 1] == 'E') || (TWOD[y][i] == 'S'&& (TWOD[y][i + 1] == 'O')))
		base->read.error = check_save_path(y, (i + 2), base);
	else if (TWOD[y][i] == 'S')
		 base->read.error = check_save_path(y, (i + 1), base);
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
