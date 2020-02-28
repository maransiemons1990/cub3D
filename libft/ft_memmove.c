/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 18:23:56 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/18 19:10:24 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			((char*)dst)[i - 1] = ((const char*)src)[i - 1];
			i--;
		}
	}
	else
	{
		while (i < len)
		{
			((char*)dst)[i] = ((const char*)src)[i];
			i++;
		}
	}
	return (dst);
}
