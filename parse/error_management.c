/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:30:55 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/17 14:15:06 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	start_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '|')
		return (0);
	return (1);
}

int	error_management(char *line)
{
	if (!unique_quote(line))
		return (0);
	if (!successive_redirect(line))
		return (0);
	if (!is_token_at_last(line))
		return (0);
	if (!start_pipe(line))
		return (0);
	return (1);
}
