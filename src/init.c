/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:49:57 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/02 05:11:28 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_general*	init_general(char **env_arg)
{
	t_general	*general;
	
	general = (t_general *) ft_calloc(1, sizeof(t_general));
	general->env = get_env(env_arg);
	general->args = NULL;
	general->last_exit_status = 0;
	general->pipe_list = NULL;
	return (general);
}

t_pipe	*init_pipe()
{
	t_pipe	*tmp;

	tmp = (t_pipe *) ft_calloc(1, sizeof(t_pipe));
	tmp->content = NULL;
	tmp->next = NULL;
	return (tmp);
}
