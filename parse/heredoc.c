/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:23:52 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/27 13:32:38 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	heredoc(char *delimiter, char *filename, int f)
{
	int		fd_tmp;

	fd_tmp = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd_tmp == -1)
		return (perror("heredoc"), 0);
	loop_heredoc(fd_tmp, delimiter, f);
	close(fd_tmp);
	return (1);
}

static int	exec_heredoc(t_pipe *pip)
{
	t_heredoc	*tmp;
	t_heredoc	*tmp1;

	tmp = pip->heredoc_list;
	while (tmp)
	{
		tmp1 = tmp->next;
		if (!heredoc(tmp->delimiter, pip->heredoc_file, tmp->expand))
			return (free_all(get_general()), 0);
		tmp = tmp1;
	}
	return (1);
}

static void	inside_child_heredoc(t_general *general)
{
	t_pipe	*tmp;
	t_pipe	*tmp1;

	heredoc_signals();
	tmp = general->pipe_list;
	general->is_parent = 0;
	general->no_child = 0;
	while (tmp)
	{
		tmp1 = tmp->next;
		if (!exec_heredoc(tmp))
			exit (0);
		tmp = tmp1;
	}
	free_all(general);
	exit (1);
}

int	all_heredoc(t_general *general)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == 0)
		inside_child_heredoc(general);
	general->no_child = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (general->no_child = 0, WEXITSTATUS(status));
	return (1);
}
