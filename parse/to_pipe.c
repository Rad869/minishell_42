/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:20:33 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/27 10:53:38 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	append_pipe_content(t_general *general, char *content)
{
	t_pipe	**last_pipe;

	if (!general->pipe_list)
		general->pipe_list = init_pipe();
	last_pipe = &general->pipe_list;
	while ((*last_pipe)->next)
		last_pipe = &(*last_pipe)->next;
	add_last_list(&(*last_pipe)->content, content);
}

static void	add_pipe(t_general *general)
{
	t_pipe	**pipe_var;

	if (!general->pipe_list)
		general->pipe_list = init_pipe();
	pipe_var = &general->pipe_list;
	while ((*pipe_var))
		pipe_var = &(*pipe_var)->next;
	*pipe_var = init_pipe();
}

static void	parse_each_pipe(t_pipe **pip)
{
	t_pipe	**tmp;
	t_pipe	**tmp1;

	tmp = pip;
	while (*tmp)
	{
		tmp1 = &((*tmp)->next);
		parse_redir(tmp);
		tmp = tmp1;
	}
}

static void	count_cmds(t_general *general)
{
	t_pipe	*tmp;

	tmp = general->pipe_list;
	while (tmp)
	{
		general->nbr_cmds++;
		tmp = tmp->next;
	}
	affect_heredoc_name(general->pipe_list);
}

int	to_pipe(t_general *general)
{
	t_list_args	*tmp;
	t_list_args	*tmp2;

	tmp = general->args;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (ft_strncmp(tmp->content, "|", 1) == 0)
		{
			add_pipe(general);
			tmp = tmp2;
			tmp2 = tmp->next;
		}
		append_pipe_content(general, ft_strdup(tmp->content));
		tmp = tmp2;
	}
	parse_each_pipe(&general->pipe_list);
	change_expand_pipe(general->pipe_list, general);
	count_cmds(general);
	free_list_args(&(general->args));
	general->args = NULL;
	return (all_heredoc(general));
}
