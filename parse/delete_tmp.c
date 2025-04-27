/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:16:34 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/25 12:45:53 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	delete_file_tmp(char *name)
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
	else
		wait(NULL);
}

void	delete_all_tmp(t_general *general)
{
	t_pipe	*tmp;
	t_pipe	*tmp1;

	tmp = general->pipe_list;
	while (tmp)
	{
		tmp1 = tmp->next;
		if (tmp->heredoc_file)
		{
			if (access(tmp->heredoc_file, F_OK) == 0)
				delete_file_tmp(tmp->heredoc_file);
		}
		tmp = tmp1;
	}
}
