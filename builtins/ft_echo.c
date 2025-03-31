/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:33:08 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:13 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (i < argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
