/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:43:54 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/17 12:51:15 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				save_path_substr(int y, int i, char **identifier, t_base *base)
{
	int ret;

	if (*identifier != NULL)
		return (base->read.error = 3);
	*identifier = ft_substr(TWOD[y], i, (ft_strlen(TWOD[y]) - i)); //m check (main)
	ret = open(*identifier, O_RDONLY);
	if (ret == -1)
		return (base->read.error = 9);
	if (*identifier == NULL)
		return (base->read.error = 6);
	return (0);
}

int				check_pathstart(int y, int *i, t_base *base)
{
	while (TWOD[y][*i] == ' ')
		(*i)++;
	if (TWOD[y][*i] == '.' && TWOD[y][*i + 1] == '/')
		return (0);
	else
		return (base->read.error = 5);
}

int				cfr_endspaces(int y, int i, t_base *base)
{
	while (TWOD[y][i])
	{
		if (TWOD[y][i] == ' ')
			i++;
		else
			return (base->read.error = 4);
	}
	return (0);
}

int				create_trgb_colorcode(int y, int entry_i, t_base *base)
{
	if (TWOD[y][entry_i] == 'C')
	{
		if (!(READ.c_color == -1))
			return (base->read.error = 3);
		READ.c_color = (0 << 24 | base->read.red << 16 | base->read.green << 8
		| base->read.blue);
	}
	if (TWOD[y][entry_i] == 'F')
	{
		if (!(READ.f_color == -1))
			return (base->read.error = 3);
		READ.f_color = (0 << 24 | base->read.red << 16 | base->read.green << 8
		| base->read.blue);
	}
	return (0);
}

int				cfr_itoa(int y, int *i, t_base *base, int cf_blue_green)
{
	int number;
	int nb_present;

	number = 0;
	nb_present = 0;
	while (TWOD[y][*i] == ' ')
		(*i)++;
	if (cf_blue_green)
	{
		if (TWOD[y][*i] == ',')
			(*i)++;
		else
			return (-1);
		while (TWOD[y][*i] == ' ')
			(*i)++;
	}
	while (TWOD[y][*i] >= '0' && TWOD[y][*i] <= '9')
	{
		number = (number * 10) + TWOD[y][*i] - '0';
		(*i)++;
		nb_present = 1;
	}
	return (nb_present == 1 ? number : -1);
}
