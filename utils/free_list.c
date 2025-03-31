/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:33:40 by rrabeari          #+#    #+#             */
/*   Updated: 2025/03/31 00:48:33 by rrabeari         ###   ########.fr       */
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
		free(env->value);
		tmp = env->next;
		free(env);
	}
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}
