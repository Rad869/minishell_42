/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:53:56 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:53:57 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*par;
	t_list	*value;

	if (!lst || !f || !del)
		return (NULL);
	value = NULL;
	while (lst)
	{
		par = ft_lstnew(f(lst->content));
		if (!par)
		{
			ft_lstclear(&value, del);
			return (NULL);
		}
		ft_lstadd_back(&value, par);
		lst = lst->next;
	}
	return (value);
}
