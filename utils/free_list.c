/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:33:40 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/24 23:54:02 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list_args(t_list_args **list)
{
	t_list_args	*tmp;
	t_list_args	*tmp2;

	tmp = *list;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
		tmp = tmp2;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		env = tmp;
		free(env->name);
		if (env->value)
			free(env->value);
		tmp = env->next;
		free(env);
	}
	free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

void	remove_elem_list(t_list_args *prev, t_list_args *n,
			t_list_args *value, t_pipe *p)
{
	free(value->next->content);
	free(value->next);
	free(value->content);
	free(value);
	if (prev)
		prev->next = n;
	else
		p->content = n;
	if (n)
		n->prev = prev;
}
