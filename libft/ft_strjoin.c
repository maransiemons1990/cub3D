/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 09:38:37 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/18 15:24:12 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strcpy(char *dest, char const *src1, char const *src2)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (src1[i] != '\0')
	{
		dest[i] = src1[i];
		i++;
	}
	while (src2[c] != '\0')
	{
		dest[i] = src2[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1, s2);
	return (str);
}
