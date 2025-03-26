/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:54:21 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:54:23 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*par;

	i = 1;
	if (!lst)
		return (0);
	par = lst;
	while (par->next != NULL)
	{
		i++;
		par = par->next;
	}
	return (i);
}
