/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 17:28:15 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/11 17:28:21 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_intlength(long n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int			len;
	char		*result;
	long		nb;

	nb = n;
	len = ft_intlength(nb);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	len--;
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		result[len] = (nb % 10) + '0';
		nb = nb / 10;
		len--;
	}
	return (result);
}
