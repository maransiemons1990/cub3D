/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 09:59:19 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/08 13:29:22 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *b1;

	b1 = b;
	while (len > 0)
	{
		*b1 = (unsigned char)c;
		b1++;
		len--;
	}
	return (b);
}
