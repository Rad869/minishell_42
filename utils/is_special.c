/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:55:33 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/23 06:59:47 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special(char *line)
{
	if (ft_strncmp(line, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(line, "<", 1) == 0)
		return (1);
	if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	if (ft_strncmp(line, "|", 1) == 0)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (1);
	return (0);
}
