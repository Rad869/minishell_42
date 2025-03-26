/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:58:12 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/05 08:19:29 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_simple_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != '\'')
		i++;
	if (line[i])
		return (i);
	return (0);
}

static int	check_double_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != '\"')
		i++;
	if (line[i])
		return (i);
	return (0);
}

int	unique_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			if (check_simple_quote(line + i))
				i += check_simple_quote(line + i);
			else
				return (0);
		}
		if (line[i] == '\"')
		{
			if (check_double_quote(line + i))
				i += check_double_quote(line + i);
			else
				return (0);
		}
		i++;
	}
	return (1);
}
