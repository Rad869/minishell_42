/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_at_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:59:30 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/22 10:57:43 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_token_at_last(char *line)
{
	t_list_args	*list;
	t_list_args	*tmp;

	list = get_list_args(ft_strdup(line));
	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp && is_special(tmp->content))
		return (free_list_args(&list), 0);
	return (free_list_args(&list), 1);
}
