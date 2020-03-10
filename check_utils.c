/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:43:54 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/10 16:44:47 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			return (1); //invalid identifier format
	}
	return (0);
}

int				check_pathstart(int y, int *i, t_base *base)
{
	while (TWOD[y][*i] == ' ')
		(*i)++;
	if (TWOD[y][*i] == '.' && TWOD[y][*i + 1] == '/')
		return (0);
	else
		return (1); //Invalid path
}

int				save_path_substr(int y, int i, char **identifier, t_base *base)//freeeeee
{
	if (*identifier != NULL)
		return (1); // Multiple identifiers
	*identifier = ft_substr(TWOD[y], i, (ft_strlen(TWOD[y]) - i));
	if (*identifier == NULL)
		return (1); //malloc failed
	return (0);
}
