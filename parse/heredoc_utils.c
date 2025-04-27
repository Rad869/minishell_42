/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:36 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/24 11:58:53 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_exp_name(char *line, int *j)
{
	char	*name;
	int		i;

	i = 0;
	*j += 1;
	if (line[i + *j] && line[i + *j] == '?')
		return (ft_strdup("?"));
	while (line[i + *j] && ft_isalnum((int) line[i + *j]))
		i++;
	name = (char *) ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (line[*j] && ft_isalnum((int) line[*j]))
		name[i++] = line[(*j)++];
	name[i] = '\0';
	(*j)--;
	return (name);
}

static char	*find_env(char *name, t_general *general)
{
	t_env	*tmp;
	char	*value;

	tmp = general->env;
	if (name && ft_strncmp(name, "?", 1) == 0)
		return (free(name), ft_itoa(general->last_exit_status));
	if (name && ft_isdigit(name[0]))
	{
		value = ft_strdup(name + 1);
		free(name);
		return (value);
	}
	while (tmp && ft_strncmp(name, tmp->name, INT_MAX) != 0)
		tmp = tmp->next;
	free(name);
	if (!tmp)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

static void	sub_value(char *buf, char *subst, int *k)
{
	int	i;

	i = 0;
	while (subst[i])
	{
		buf[*k] = subst[i];
		i++;
		*k += 1;
	}
	(*k)--;
	free(subst);
}

static void	loop_expand(char (*value)[5000], char *tmp,
	t_general *general, int *k)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] && tmp[i] == '$' && tmp[i + 1] != ' '
			&& tmp[i + 1] && tmp[i + 1] != '\"')
			sub_value(*value, find_env(get_exp_name(tmp, &i), general), k);
		else
			(*value)[*k] = tmp[i];
		if (tmp[i])
			i++;
		(*k) += 1;
	}
}

void	expande_heredoc(char **line, t_general *general, int f)
{
	char	value[5000];
	int		k;
	char	*tmp;

	if (!f)
		return ;
	k = 0;
	tmp = *line;
	loop_expand(&value, tmp, general, &k);
	value[k] = 0;
	free(*line);
	*line = ft_strdup(value);
}
