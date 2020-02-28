/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:55:29 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/15 14:48:32 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	c;
	size_t	total_len;

	i = ft_strlen(dst);
	c = ft_strlen(src);
	total_len = i + c;
	if (dstsize > i)
	{
		c = 0;
		while (c < dstsize - i - 1 && src[c])
		{
			dst[i + c] = src[c];
			c++;
		}
		dst[i + c] = '\0';
		return (total_len);
	}
	return (c + dstsize);
}
