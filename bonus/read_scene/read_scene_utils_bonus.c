/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene_utils_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:43:54 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/14 20:19:54 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"
#include <fcntl.h>

int				save_path_substr(int y, int i, char **identifier, t_base *base)
{
	int		ret;

	if (*identifier != NULL)
		return (error_distr(base, 3));
	*identifier = ft_substr(base->read.array[y], i,
		(ft_strlen(base->read.array[y]) - i));
	ret = open(*identifier, O_RDONLY);
	if (ret == -1)
		return (error_distr(base, 9));
	if (*identifier == NULL)
		return (error_distr(base, 6));
	return (0);
}

int				check_pathstart(int y, int *i, char **array)
{
	while (array[y][*i] == ' ')
		(*i)++;
	if (array[y][*i] == '.' && array[y][*i + 1] == '/')
		return (0);
	else
		return (1);
}

int				cfr_endspaces(int y, int i, t_base *base, t_read *read)
{
	while (read->array[y][i])
	{
		if (read->array[y][i] == ' ')
			i++;
		else
			return (error_distr(base, 4));
	}
	return (0);
}

int				cfr_itoa(int y, int *i, char **array)
{
	int		number;
	int		nb_present;

	number = 0;
	nb_present = 0;
	while (array[y][*i] == ' ')
		(*i)++;
	while (array[y][*i] >= '0' && array[y][*i] <= '9')
	{
		number = (number * 10) + array[y][*i] - '0';
		(*i)++;
		nb_present = 1;
	}
	return (nb_present == 1 ? number : -1);
}
