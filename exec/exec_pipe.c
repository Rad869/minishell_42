/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:01:46 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/24 16:22:29 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	affect_fd(t_general *general, int i,
		int (*pipefd)[500][2], t_pipe *tmp)
{
	t_pipe	*tmp1;
	int		j;

	j = 0;
	tmp1 = general->pipe_list;
	if (i > 0)
		dup2((*pipefd)[i - 1][0], STDIN_FILENO);
	if (i < general->nbr_cmds - 1)
		dup2((*pipefd)[i][1], STDOUT_FILENO);
	j = 0;
	tmp1 = general->pipe_list;
	while (tmp1->next)
	{
		close((*pipefd)[j][0]);
		close((*pipefd)[j][1]);
		tmp1 = tmp1->next;
		j++;
	}
	exec_one_process(general, tmp);
}

static void	loop_exec(t_general *general,
		pid_t (*pid)[500], int (*pipefd)[500][2])
{
	t_pipe	*tmp;
	int		i;
	pid_t	tmp_pid;

	i = 0;
	tmp = general->pipe_list;
	while (tmp)
	{
		tmp_pid = fork();
		if (tmp_pid == 0)
			affect_fd(general, i, pipefd, tmp);
		else
		{
			(*pid)[i] = tmp_pid;
			tmp = tmp->next;
			i++;
		}
	}
}

static void	close_all_pipefd(int (*pipefd)[500][2], t_general *general)
{
	int		j;
	t_pipe	*tmp1;

	j = 0;
	tmp1 = general->pipe_list;
	while (tmp1->next)
	{
		close((*pipefd)[j][0]);
		close((*pipefd)[j][1]);
		tmp1 = tmp1->next;
		j++;
	}
}

static int	waiting_all_pid(t_general *general,
		int (*pipefd)[500][2], pid_t (*pid)[500])
{
	int		j;
	t_pipe	*tmp1;

	j = 0;
	tmp1 = general->pipe_list;
	close_all_pipefd(pipefd, general);
	while (tmp1->next)
	{
		waitpid((*pid)[j], NULL, 0);
		tmp1 = tmp1->next;
		j++;
	}
	return (j);
}

void	exec_pipe(t_pipe *pip, t_general *general)
{
	int		pipefd[500][2];
	pid_t	pid[500];
	t_pipe	*tmp;
	int		i;
	int		status;

	i = 0;
	tmp = pip;
	while (tmp->next)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			exit (1);
		}
		i++;
		tmp = tmp->next;
	}
	loop_exec(general, &pid, &pipefd);
	waitpid(pid[waiting_all_pid(general, &pipefd, &pid)], &status, 0);
	free_all(general);
	if (WIFEXITED(status))
		exit (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(signal_message(NULL, WTERMSIG(status)));
}
