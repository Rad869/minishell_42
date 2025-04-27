/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:06:59 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/25 12:12:02 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir	*tmp1;

	tmp = redir;
	while (tmp)
	{
		tmp1 = tmp->next;
		free(tmp->filename);
		free(tmp);
		tmp = tmp1;
	}
}

static void	free_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*tmp;
	t_heredoc	*tmp1;

	tmp = heredoc;
	while (tmp)
	{
		tmp1 = tmp->next;
		free(tmp->delimiter);
		free(tmp);
		tmp = tmp1;
	}
}

void	free_pipe(t_pipe **pip)
{
	t_pipe	*tmp;
	t_pipe	*tmp1;

	tmp = *pip;
	while (tmp)
	{
		tmp1 = tmp->next;
		free_list_args(&tmp->content);
		free_redir(tmp->redir_list);
		free_heredoc(tmp->heredoc_list);
		if (tmp->fd[0] != -1)
			close(tmp->fd[0]);
		if (tmp->fd[1] != -1)
			close(tmp->fd[1]);
		if (tmp->heredoc_file)
			free(tmp->heredoc_file);
		double_free(tmp->argv);
		double_free(tmp->env);
		free(tmp);
		tmp = tmp1;
	}
	(*pip) = NULL;
}
