/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:38:32 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/10 08:15:16 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_eof(t_general *general)
{
	printf("exit\n");
	clear_history();
	free_general(general);
	exit(general->signal->exit_status);
}