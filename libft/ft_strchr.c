/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 18:25:18 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/08 14:47:49 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c1;

	i = 0;
	c1 = c;
	while (s[i] != '\0')
	{
		if (s[i] == c1)
			return ((char *)s + i);
		i++;
	}
	if (c1 == '\0')
		return ((char *)s + i);
	return (NULL);
}
