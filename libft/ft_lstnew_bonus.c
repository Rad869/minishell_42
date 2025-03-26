/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:54:05 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 12:54:06 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*value;

	value = (t_list *)malloc(sizeof(t_list));
	if (!value)
		return (NULL);
	value->content = content;
	value->next = NULL;
	return (value);
}
