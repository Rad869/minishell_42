/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:36:03 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/26 18:34:54 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	error_handling(char **argv, t_general *ret)
{
	if (argv[1] && argv[1][0] == '-' && argv[1][1] != 0)
	{
		write(2, "env: invalid option\n", 20);
		ret->last_exit_status = 125;
		return (1);
	}
	else if (argv[1] && argv[1][0] == '-' && argv[1][1] == 0)
		return (0);
	write(2, "env: Not a directory\n", 21);
	ret->last_exit_status = 126;
	return (1);
}

int	ft_env(int argc, char **argv, t_general *ret)
{
	char		**env;
	int			i;

	if (argc > 1)
		return (error_handling(argv, ret));
	i = 0;
	env = convert_env_to_char(ret->env);
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	ret->last_exit_status = 0;
	return (double_free(env), 0);
}
