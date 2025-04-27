/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:09:32 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/25 17:12:16 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_data(t_general *general)
{
	if (general->pipe_list)
	{
		free_pipe(&general->pipe_list);
		general->pipe_list = NULL;
	}
}

void	free_all(t_general *general)
{
	free_data(general);
	free_env(general->env);
	close(general->default_fd[0]);
	close(general->default_fd[1]);
	close (0);
	close (1);
	rl_clear_history();
	free(general);
}

void	delete_file_tmp(char *name)
{
	char	**argv;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		argv = (char **) malloc(sizeof(char *) * 4);
		argv[0] = ft_strdup("/bin/rm");
		argv[1] = ft_strdup("-rf");
		argv[2] = name;
		argv[3] = NULL;
		execve(argv[0], argv, NULL);
		double_free(argv);
		perror("rm");
		exit (1);
	}
}
