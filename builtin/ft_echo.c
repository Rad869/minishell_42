/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:33:08 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/24 11:30:27 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_flag(char *argv, int *j)
{
	int		i;

	i = 2;
	if (ft_strlen(argv) != 0 && ft_strncmp(argv, "-n", 2) == 0)
	{
		while (argv[i] == 'n')
			i++;
		if (argv[i] == '\0')
			return (*j += 1, 1);
	}
	return (0);
}

int	ft_echo(int argc, char **argv, t_general *ret)
{
	int	i;
	int	n_flag;
	int	end;

	i = 1;
	end = 1;
	n_flag = 0;
	if (argc > 1)
		n_flag = check_flag(argv[1], &i);
	while (end && argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
		end = check_flag(argv[i], &i);
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (i < argc - 1)
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	ret->last_exit_status = 0;
	return (0);
}
