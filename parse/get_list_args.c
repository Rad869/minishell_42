/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:12 by rrabeari          #+#    #+#             */
/*   Updated: 2025/03/31 00:47:02 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_quote(char *line, int *i, char c)
{
	char	*value;
	int		j;
	int		k;

	j = 1;
	k = 0;
	while (line[*i + j] && line[*i + j] != c)
		j++;
	value = (char *) ft_calloc(j + 2, sizeof(char));
	*i += 1;
	while (line[*i] && line[*i] != c)
	{
		value[k] = line[*i];
		k++;
		*i += 1;
	}
	value[k] = c;
	value[k + 1] = '\0';
	*i += 1;
	return (value);
}

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
	return (ft_strdup(""));
}

static void	add_last_list(t_list_args **list, char *content)
{
	t_list_args	*tmp;
	t_list_args	*tmp2;

	tmp = (t_list_args *) malloc(sizeof(t_list_args));
	tmp->content = NULL;
	tmp->content = content;
	tmp->next = NULL;
	if (*list == NULL)
	{
		*list = tmp;
		return ;
	}
	tmp2 = *list;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
}

static char	*get_word(char *line, int *i)
{
	int		j;
	int		k;
	char	*value;

	j = 0;
	k = 0;
	while (line[*i + j] && line[*i + j] != ' ' &&
		!is_special(line + *i + j))
		j++;
	value = (char *) ft_calloc(j + 1, sizeof(char));
	if (!value)
		return (NULL);
	while (line[*i] && line[*i] != ' ' && !is_special(line + *i))
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
	int				i;
	t_list_args	*list;

	i = 0;
	list = NULL;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && (line[i] == '\'' || line[i] == '\"'))
			add_last_list(&list, get_quote(line, &i, line[i]));
		else if (line[i] && is_special(line + i))
			add_last_list(&list, get_special_char(line, &i));
		else
			add_last_list(&list, get_word(line, &i));
		while (line[i] && line[i] == ' ')
			i++;
	}
	free (line);
	return (list);
}
