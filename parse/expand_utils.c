/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 05:28:26 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 23:55:02 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_expand_list(t_list_args *list, t_general *general)
{
	t_list_args	*tmp;
	t_list_args	*tmp1;

	tmp = list;
	while (tmp)
	{
		tmp1 = tmp->next;
		expand(&tmp->content, general);
		remove_quote(&tmp->content);
		tmp = tmp1;
	}
}

static void	change_expand_redir(t_redir *redir, t_general *general)
{
	t_redir	*tmp;
	t_redir	*tmp1;

	tmp = redir;
	while (tmp)
	{
		tmp1 = tmp->next;
		expand(&tmp->filename, general);
		remove_quote(&tmp->filename);
		tmp = tmp1;
	}
}

static void	remove_quote_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*tmp;
	t_heredoc	*tmp1;

	tmp = heredoc;
	while (tmp)
	{
		tmp1 = tmp->next;
		remove_quote(&tmp->delimiter);
		tmp = tmp1;
	}
}

void	change_expand_pipe(t_pipe *pipe, t_general *general)
{
	t_pipe	*tmp;
	t_pipe	*tmp1;

	tmp = pipe;
	while (tmp)
	{
		tmp1 = tmp->next;
		change_expand_list(tmp->content, general);
		change_expand_redir(tmp->redir_list, general);
		remove_quote_heredoc(tmp->heredoc_list);
		tmp->argv = convert_list_to_char(tmp->content);
		tmp->env = convert_env_to_char(general->env);
		tmp = tmp1;
	}
}

void	affect_expand_value(char (*value)[5000], char *tmp, int *k, int *i)
{
	(*value)[(*k)++] = tmp[(*i)++];
	while (tmp[*i] && tmp[*i] != '\'')
		(*value)[(*k)++] = tmp[(*i)++];
	(*value)[(*k)++] = tmp[(*i)++];
}
