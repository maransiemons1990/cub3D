/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_cub3d_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:28 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/10 13:38:00 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t			ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char			*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc((ft_strlen(s1) + 1) * (sizeof(char)));
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
** Beginning of strjoin
*/

static	char	*ft_strpaste(char *dest, char const *src1, char const *src2)
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

char			*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strpaste(str, s1, s2);
	free(s1);
	free(s2);
	return (str);
}
