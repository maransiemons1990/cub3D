/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 10:41:39 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/19 18:59:40 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	c;
	size_t	i;

	c = 0;
	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (len > c && haystack[c])
	{
		while (needle[i] == haystack[c + i] && needle[i] && c + i < len)
		{
			i++;
			if (needle[i] == '\0')
				return ((char *)haystack + c);
		}
		i = 0;
		c++;
	}
	return (NULL);
}
