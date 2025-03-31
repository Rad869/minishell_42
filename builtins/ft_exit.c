/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:36:27 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:17 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int argc, char **argv)
{
	int	status;

	if (argc > 1)
	{
		status = ft_atoi(argv[1]);
		exit(status);
	}
	exit(0);
}
