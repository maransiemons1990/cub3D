/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 19:26:50 by msiemons       #+#    #+#                */
/*   Updated: 2019/12/09 16:56:00 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	strlen_s;

	i = 0;
	if (!s)
		return (NULL);
	strlen_s = ft_strlen(s);
	if (start > strlen_s)
		return (ft_strdup(""));
	if (strlen_s - start < len)
		len = strlen_s - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len && start < strlen_s)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
