/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:20:33 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/02 05:39:41 by rrabeari         ###   ########.fr       */
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

static void add_pipe(t_general *general)
{
	t_pipe	**pipe_var;

	if (!general->pipe_list)
		general->pipe_list = init_pipe();
	pipe_var = &general->pipe_list;
	while ((*pipe_var))
		pipe_var = &(*pipe_var)->next;
	*pipe_var = init_pipe();
}

void	to_pipe(t_general *general)
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
	free_list_args(&general->args);
	general->args = NULL;
}

void	free_pipe(t_pipe **pipe_list)
{
	t_pipe	*tmp_pipe;
	t_pipe	*tmp2_pipe;

	tmp_pipe = *pipe_list;
	while(tmp_pipe)
	{
		tmp2_pipe = tmp_pipe->next;
		free_list_args(&tmp_pipe->content);
		free(tmp_pipe);
		tmp_pipe = tmp2_pipe;
	}
}
