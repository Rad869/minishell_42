/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.C                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:47:11 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/22 14:53:44 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fd_management(t_pipe *pip)
{
	if (pip->input_type == 1)
	{
		if (pip->fd[0] != -1)
			close(pip->fd[0]);
		pip->heredoc_fd = open(pip->heredoc_file, O_RDONLY);
		if (pip->heredoc_fd == -1)
			perror("open");
		dup2(pip->heredoc_fd, STDIN_FILENO);
		close(pip->heredoc_fd);
		pip->heredoc_fd = -1;
	}
}
