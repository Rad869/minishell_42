/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args_to_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 02:00:34 by rrabeari          #+#    #+#             */
/*   Updated: 2025/03/31 02:30:59 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	affect_value(t_list_args *args, char **value)
{
	t_list_args	*tmp;
	t_list_args	*tmp2;
	int			i;

	tmp = args;
	i = 0;
	while (tmp)
	{
		tmp2 = tmp->next;
		value[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp2;
	}
}

char	**convert_list_to_char(t_list_args *args)
{
	char	**value;
	int		i;
	t_list_args *tmp;
	t_list_args *tmp2;

	tmp = args;
	i = 0;
	while (tmp)
	{
		tmp2 = tmp->next;
		i++;
		tmp = tmp2;
	}
	value = (char **) ft_calloc(i + 1, sizeof(char *));
	affect_value(args, value);
	return (value);
}