/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 08:09:18 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/14 10:43:20 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_quote(char **line)
{
	char	value[5000];
	int		i;
	int		k;
	char	quote;

	i = 0;
	k = 0;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
		{
			quote = (*line)[i++];
			while ((*line)[i] && (*line)[i] != quote)
				value[k++] = (*line)[i++];
			i++;
		}
		else if ((*line)[i])
			value[k++] = (*line)[i++];
	}
	value[k] = '\0';
	free(*line);
	*line = ft_strdup(value);
}
