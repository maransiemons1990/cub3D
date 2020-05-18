/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 12:53:35 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/22 14:16:40 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		if (lst->next == NULL)
			return (lst);
		else
			return (ft_lstlast(lst->next));
	}
	return (NULL);
}
