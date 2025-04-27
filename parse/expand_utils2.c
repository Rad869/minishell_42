/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:03:06 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 23:56:05 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_tild(char **line, t_general *g)
{
	char	*value;

	if (*line && (*line)[0] == '~' && ((*line)[1] == ' '
		|| (*line)[1] == 0 || (*line)[1] == '/'))
	{
		if (!g->home)
		{
			write(2, "HOME env does not set\n", 22);
			g->last_exit_status = 1;
		}
		value = ft_strjoin(g->home, *line + 1);
		free(*line);
		*line = value;
		return (0);
	}
	return (1);
}
