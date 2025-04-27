/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:26:48 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/27 12:02:25 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	only_builtin(t_general *general, t_pipe *pip)
{
	char	**argv;
	int		argc;

	if (!exec_redirection(pip))
		return (0);
	fd_management(pip);
	argv = convert_list_to_char(pip->content);
	argc = count_argv(argv);
	if (!exec_builtin2(argv, argc, general)
		|| !exec_builtin(argv, argc, general))
		return (double_free(argv), 0);
	return (double_free(argv), 1);
}

void	exec_one_process(t_general *general, t_pipe *pip)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
	general->is_parent = 0;
	if (!exec_redirection(pip))
	{
		free_all(general);
		exit (1);
	}
	put_full_path(&pip->argv[0], general);
	fd_management(pip);
	builtins_in_exec(general, pip);
	execve(pip->argv[0], pip->argv, pip->env);
	access_error(general, pip);
	write(2, pip->argv[0], ft_strlen(pip->argv[0]));
	write(2, ": Command not found\n", 20);
	free_all(general);
	exit(127);
}

int	exec(t_general *general)
{
	int		wstatus;
	int		pid;

	wstatus = 0;
	if (is_builtin(general->pipe_list->argv[0]) || !general->pipe_list->argv[0])
	{
		if (!only_builtin(general, general->pipe_list))
			return (0);
		else
			return (1);
	}
	general->no_child = 0;
	pid = fork();
	if (pid == 0)
		exec_one_process(general, general->pipe_list);
	else
	{
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			general->last_exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			general->last_exit_status
				= signal_message(general, WTERMSIG(wstatus));
	}
	return (1);
}

int	exec_command(t_general *general)
{
	t_pipe	*pip;
	pid_t	pid;
	int		wstatus;

	pip = general->pipe_list;
	if (pip && !pip->next)
	{
		if (!exec(general))
			return (0);
	}
	else if (pip && pip->next)
	{
		general->no_child = 0;
		pid = fork();
		if (pid == 0)
			exec_pipe(pip, general);
		else
		{
			waitpid(-1, &wstatus, 0);
			if (WIFEXITED(wstatus))
				general->last_exit_status = WEXITSTATUS(wstatus);
		}
	}
	return (1);
}
