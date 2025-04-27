/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:11:53 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/23 20:00:31 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_builtin(char **argv, int argc, t_general *general)
{
	if (argc == 0)
		return (0);
	if (ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) == 0)
	{
		if (ft_cd(argc, argv, general) != 0)
			return (0);
	}
	else if (ft_strncmp(argv[0], "echo", ft_strlen(argv[0])) == 0)
	{
		if (ft_echo(argc, argv, general) != 0)
			return (0);
	}
	else if (ft_strncmp(argv[0], "env", ft_strlen(argv[0])) == 0)
	{
		if (ft_env(argc, argv, general) != 0)
			return (0);
	}
	else if (ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) == 0)
	{
		if (ft_exit(argc, argv, general) != 0)
			return (0);
	}
	return (1);
}

int	exec_builtin2(char **argv, int argc, t_general *general)
{
	if (argc == 0 || ft_strlen(argv[0]) == 0)
		return (0);
	if (ft_strncmp(argv[0], "export", ft_strlen(argv[0])) == 0)
	{
		if (ft_export(argc, argv, general) != 0)
			return (0);
	}
	else if (ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])) == 0)
	{
		if (ft_pwd(argc, argv, general) != 0)
			return (0);
	}
	else if (ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0)
	{
		if (ft_unset(argc, argv, general) != 0)
			return (0);
	}
	return (1);
}
