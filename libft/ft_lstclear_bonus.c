/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:53:29 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:53:30 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list	**lst, void (*del)(void *))
{
	t_list	*par;

	while (*lst)
	{
		par = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = par;
	}
	free(*lst);
	*lst = NULL;
}
