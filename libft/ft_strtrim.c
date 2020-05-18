/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 10:34:05 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/19 20:11:55 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == NULL)
			break ;
		i++;
	}
	if (s1[i] == '\0')
		return (ft_strdup(""));
	while (len)
	{
		if (ft_strchr(set, s1[len - 1]) == NULL)
			break ;
		len--;
	}
	len = len - i;
	str = ft_substr(s1, i, len);
	return (str);
}
