/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:16:37 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/27 00:45:48 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	input_redirection(t_pipe *pip, char *filename)
{
	if (pip->fd[0] != -1)
		close (pip->fd[0]);
	pip->fd[0] = open(filename, O_RDONLY);
	if (pip->fd[0] == -1)
		return (0);
	dup2(pip->fd[0], STDIN_FILENO);
	close (pip->fd[0]);
	return (1);
}

static int	output_redirection(t_pipe *pip, char *filename)
{
	if (pip->fd[1] != -1)
		close(pip->fd[1]);
	if (!access_output(filename))
		return (0);
	pip->fd[1] = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (pip->fd[1] == -1)
		return (perror(filename), 0);
	dup2(pip->fd[1], STDOUT_FILENO);
	return (1);
}

static int	output_append(t_pipe *pip, char *filename)
{
	if (pip->fd[1] != -1)
		close(pip->fd[1]);
	if (!access_output(filename))
		return (0);
	pip->fd[1] = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (pip->fd[1] == -1)
		return (perror(filename), 0);
	dup2(pip->fd[1], STDOUT_FILENO);
	return (1);
}

static int	condition_redirection(t_pipe *pip, t_redir *tmp)
{
	if (tmp->type == INPUT_REDIR)
	{
		if (!input_redirection(pip, tmp->filename))
			return (perror(tmp->filename), 0);
	}
	else if (tmp->type == OUTPUT_REDIR)
	{
		if (!output_redirection(pip, tmp->filename))
			return (0);
	}
	else if (tmp->type == OUTPUT_APPEND)
	{
		if (!output_append(pip, tmp->filename))
			return (0);
	}
	return (1);
}

int	exec_redirection(t_pipe *pip)
{
	t_redir	*tmp;

	tmp = pip->redir_list;
	while (tmp)
	{
		if (!condition_redirection(pip, tmp))
			return (0);
		tmp = tmp->next;
	}
	if (!(*(pip->argv)))
		return (0);
	return (1);
}
