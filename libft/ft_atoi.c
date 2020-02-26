/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 16:55:54 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/20 10:56:42 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int					i;
	int					minpos;
	unsigned long long	result;

	i = 0;
	minpos = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
		minpos = -1;
	if (str[i] == 45 || str[i] == 43)
		i++;
	while ((str[i] >= 48 && str[i] <= 57))
	{
		result = (result * 10) + str[i] - 48;
		i++;
		if (result >= 9223372036854775808ULL && minpos == 1)
			return (-1);
		if (result >= 9223372036854775808ULL && minpos == -1)
			return (0);
	}
	return (minpos * result);
}
