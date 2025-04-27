/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:36:27 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/25 11:18:19 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_isnumeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	is_normal_sizepos(char *arg)
{
	if (arg && (arg[0] == '+' || arg[0] == '-'))
		arg++;
	while (arg && *arg == '0')
		arg++;
	if (ft_strlen(arg) == 19)
	{
		if (ft_strncmp("9223372036854775807", arg, 19) >= 0)
			return (1);
		return (0);
	}
	else if (ft_strlen(arg) > 19)
		return (0);
	return (1);
}

int	ft_exit(int argc, char **argv, t_general *ret)
{
	int	a;

	if (argc >= 2)
	{
		if (!ft_isnumeric(argv[1]) || !is_normal_sizepos(argv[1]))
		{
			write(STDERR_FILENO, "exit\nexit: num args requierd\n", 29);
			ret->last_exit_status = 2;
			free_all(ret);
			double_free(argv);
			exit(2);
		}
		if (argc > 2)
			return (write(STDERR_FILENO, "exit\nexit: too many args\n", 25),
				ret->last_exit_status = 1, 1);
		a = (unsigned char) ft_atoi(argv[1]);
		free_all(ret);
		double_free(argv);
		exit(a);
	}
	a = ret->last_exit_status;
	free_all(ret);
	double_free(argv);
	exit(a);
}
