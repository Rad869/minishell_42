/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:49:57 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 20:37:15 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_general	*get_general(void)
{
	static t_general	*general;
	static int			created;

	if (!created)
	{
		created = 1;
		general = (t_general *) ft_calloc(1, sizeof(t_general));
	}
	return (general);
}

t_general	*init_general(char **env_arg)
{
	t_general	*general;

	general = get_general();
	general->env = get_env(env_arg);
	general->args = NULL;
	general->last_exit_status = 0;
	general->pipe_list = NULL;
	general->default_fd[0] = dup(STDIN_FILENO);
	general->default_fd[1] = dup(STDOUT_FILENO);
	general->nbr_cmds = 0;
	general->no_child = 1;
	general->is_parent = 1;
	general->home = getenv("HOME");
	signals();
	return (general);
}

t_pipe	*init_pipe(void)
{
	t_pipe	*tmp;

	tmp = (t_pipe *) ft_calloc(1, sizeof(t_pipe));
	tmp->content = NULL;
	tmp->next = NULL;
	tmp->heredoc_list = NULL;
	tmp->redir_list = NULL;
	tmp->fd[0] = -1;
	tmp->fd[1] = -1;
	tmp->heredoc_fd = -1;
	tmp->heredoc_file = NULL;
	tmp->argc = 0;
	tmp->argv = NULL;
	tmp->env = NULL;
	tmp->pid = -1;
	return (tmp);
}
