/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   successive_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:32:56 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 21:23:50 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	jump_to_next(char *line, char c)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

static int	check_multi_double(char *line, char c, int *j)
{
	int	i;

	i = 1;
	if (line[i - 1] == '|')
		return (*j += 1, 1);
	if (line[i])
	{
		if (line[i] == c)
		{
			i++;
			if (line[i] == '>' || line[i] == '<' || line[i] == '|')
				return (*j += i, 0);
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i] == '>' || line[i] == '<' || line[i] == '|')
				return (*j += i, 0);
		}
	}
	*j += i;
	return (1);
}

static int	check_multi_single(char *line, int *j)
{
	int	i;

	i = 1;
	if (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			return (*j += i, 0);
	}
	*j += i;
	return (1);
}

static int	check_pipe_redir(char *line, int *i)
{
	if (line && line[*i] == '|')
	{
		(*i)++;
		while (line[*i] && line[*i] == ' ')
			(*i)++;
		if (line[*i] == '|')
			return (0);
	}
	return (1);
}

int	successive_redirect(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += jump_to_next(line + i, line[i]);
		if (!check_pipe_redir(line, &i))
			return (0);
		if (line[i] == '>' || line[i] == '<')
		{
			if (check_multi_double(line + i, line[i], &i))
				i--;
			else
				return (0);
			if (check_multi_single(line + i, &i))
				i--;
			else
				return (0);
		}
		if (line[i])
			i++;
	}
	return (1);
}
