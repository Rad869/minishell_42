/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 06:01:25 by rrabeari          #+#    #+#             */
/*   Updated: 2025/03/31 07:45:43 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_entry(t_general *general)
{
	char	*entry;

	entry = NULL;
	signal_handler(1);
	entry = readline("Minishell>");
	if (entry == NULL)
		handle_eof(general);
	if (!error_management(entry))
		return (free(entry), perror("Minishell: parse error\n"), 0);
	general->args = get_list_args(entry);
	return (1);
}