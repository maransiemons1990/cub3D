/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:55:15 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/08 13:16:29 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst1;
	unsigned char const *src1;

	dst1 = dst;
	src1 = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n)
	{
		*dst1 = *src1;
		dst1++;
		src1++;
		n--;
	}
	return (dst);
}
