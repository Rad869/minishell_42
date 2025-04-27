/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:00:11 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 13:06:16 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtins_in_exec(t_general *general, t_pipe *pip)
{
	if (is_builtin(pip->argv[0]))
	{
		if (!only_builtin(general, pip))
		{
			free_all(general);
			exit (1);
		}
		free_all(general);
		exit (0);
	}
}

void	access_error(t_general *general, t_pipe *pip)
{
	struct stat	path;

	if (ft_strlen(pip->argv[0]) != 0 && access(pip->argv[0], F_OK) == 0
		&& (access(pip->argv[0], R_OK) == -1 || access(pip->argv[0], X_OK) == -1
			|| lstat(pip->argv[0], &path) == 0))
	{
		perror(pip->argv[0]);
		free_all(general);
		exit (126);
	}
}
