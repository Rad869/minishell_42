/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:12 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/23 06:43:34 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_special_char(char *line, int *i)
{
	if (ft_strncmp(line + *i, "|", 1) == 0)
		return (*i += 1, ft_strdup("|"));
	else if (ft_strncmp(line + *i, "<<", 2) == 0)
		return (*i += 2, ft_strdup("<<"));
	else if (ft_strncmp(line + *i, ">>", 2) == 0)
		return (*i += 2, ft_strdup(">>"));
	else if (ft_strncmp(line + *i, "<", 1) == 0)
		return (*i += 1, ft_strdup("<"));
	else if (ft_strncmp(line + *i, ">", 1) == 0)
		return (*i += 1, ft_strdup(">"));
	return (ft_strdup(""));
}

void	add_last_list(t_list_args **list, char *content)
{
	t_list_args	*tmp;
	t_list_args	**tmp2;
	t_list_args	*tmp3;

	tmp = (t_list_args *) malloc(sizeof(t_list_args));
	tmp->content = content;
	tmp->next = NULL;
	tmp->prev = NULL;
	if (*list == NULL)
	{
		*list = tmp;
		return ;
	}
	tmp2 = list;
	while ((*tmp2))
	{
		tmp3 = *tmp2;
		tmp2 = &(*tmp2)->next;
	}
	*tmp2 = tmp;
	(*tmp2)->prev = tmp3;
}

static char	*get_word(char *line, int *i)
{
	int		j;
	int		k;
	char	*value;

	j = 0;
	k = 0;
	j = get_len_word(line, *i);
	value = (char *) ft_calloc(j + 1, sizeof(char));
	if (!value)
		return (NULL);
	while (k < j)
	{
		value[k] = line[*i];
		*i += 1;
		k++;
	}
	value[k] = '\0';
	return (value);
}

t_list_args	*get_list_args(char *line)
{
	int				*i;
	t_list_args		*list;

	i = malloc(sizeof(int));
	*i = 0;
	list = NULL;
	while (line && line[*i])
	{
		while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
			(*i)++;
		if (line[*i] && !is_special(line + *i))
			add_last_list(&list, get_word(line, i));
		if (line[*i] && is_special(line + *i))
			add_last_list(&list, get_special_char(line, i));
		while (line[*i] && line[*i] == ' ')
			(*i)++;
	}
	free(i);
	if (line)
		free (line);
	return (list);
}
