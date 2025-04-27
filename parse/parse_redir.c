/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:15:02 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/24 10:40:24 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_redir(t_pipe *p, char *content, t_redir_type type)
{
	t_redir	*tmp;
	t_redir	**tmp1;

	tmp = (t_redir *) ft_calloc(1, sizeof(t_redir));
	tmp->filename = content;
	tmp->type = type;
	tmp->next = NULL;
	if (!p->redir_list)
	{
		p->redir_list = tmp;
		return ;
	}
	tmp1 = &p->redir_list;
	while (*tmp1)
		tmp1 = &(*tmp1)->next;
	*tmp1 = tmp;
}

static void	add_heredoc(t_pipe *p, char *delim)
{
	t_heredoc	*tmp;
	t_heredoc	**tmp1;

	tmp = (t_heredoc *) ft_calloc(1, sizeof(t_heredoc));
	tmp->delimiter = delim;
	tmp->expand = 1;
	if (delim && (ft_strchr(delim, '\'') || ft_strchr(delim, '\"')))
		tmp->expand = 0;
	tmp->next = NULL;
	if (!p->heredoc_list)
	{
		p->heredoc_list = tmp;
		return ;
	}
	tmp1 = &p->heredoc_list;
	while ((*tmp1))
		tmp1 = &(*tmp1)->next;
	*tmp1 = tmp;
}

static t_list_args	*aff_redir(t_pipe *p, t_list_args *tmp1, t_redir_type t)
{
	t_list_args	*tmp2;

	add_redir(p, ft_strdup(tmp1->next->content), t);
	tmp2 = (tmp1->next->next);
	if (t == INPUT_REDIR)
		p->input_type = 2;
	remove_elem_list(tmp1->prev, tmp2, tmp1, p);
	return (tmp2);
}

static t_list_args	*aff_here_doc(t_pipe *p, t_list_args *tmp1)
{
	t_list_args	*tmp2;

	add_heredoc(p, ft_strdup(tmp1->next->content));
	tmp2 = tmp1->next->next;
	p->input_type = 1;
	remove_elem_list(tmp1->prev, tmp2, tmp1, p);
	return (tmp2);
}

void	parse_redir(t_pipe **p)
{
	t_list_args	*tmp1;
	t_list_args	*tmp2;

	tmp1 = ((*p)->content);
	while (tmp1)
	{
		tmp2 = tmp1->next;
		if (ft_strncmp(tmp1->content, ">>", 2) == 0)
			tmp2 = aff_redir(*p, tmp1, OUTPUT_APPEND);
		else if (ft_strncmp(tmp1->content, "<<", 2) == 0)
			tmp2 = aff_here_doc(*p, tmp1);
		else if (ft_strncmp(tmp1->content, ">", 1) == 0)
			tmp2 = aff_redir(*p, tmp1, OUTPUT_REDIR);
		else if (ft_strncmp(tmp1->content, "<", 1) == 0)
			tmp2 = aff_redir(*p, tmp1, INPUT_REDIR);
		tmp1 = tmp2;
	}
}
