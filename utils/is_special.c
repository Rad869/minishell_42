/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:55:33 by rrabeari          #+#    #+#             */
/*   Updated: 2025/03/30 23:59:20 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special(char *line)
{
	if (ft_strncmp(line, "|", 1) == 0)
		return (1);
	if (ft_strncmp(line, "<", 1) == 0)
		return (1);
	if (ft_strncmp(line, ">", 1) == 0)
		return (1);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (1);
	return (0);
}