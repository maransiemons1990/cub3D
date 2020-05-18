/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 12:30:18 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/08 12:21:24 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dst1;
	unsigned char const	*src1;
	size_t				i;

	i = 0;
	dst1 = dst;
	src1 = src;
	while (i < n)
	{
		dst1[i] = src1[i];
		if (src1[i] == (unsigned char)c)
			return (dst + (i + 1));
		i++;
	}
	return (NULL);
}
