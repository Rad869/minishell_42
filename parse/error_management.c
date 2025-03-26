/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:30:55 by rrabeari          #+#    #+#             */
/*   Updated: 2025/02/06 07:11:06 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_management(char	*line)
{
	if (!unique_quote(line))
		return (0);
	if (!successive_redirect(line))
		return (0);
	return (1);
}
