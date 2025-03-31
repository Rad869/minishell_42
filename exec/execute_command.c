/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:26:48 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/31 08:14:13 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(int argc, char **argv)
{
	const char	*command;

	command = argv[0];
	if (argc < 1)
		return (0);
    if (ft_strcmp(command, "echo") == 0)
		return (ft_echo(argc, argv));
	if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(argc, argv));
    if (ft_strcmp(command, "pwd") == 0)
		return (ft_pwd(argc, argv));
	if (ft_strcmp(command, "export") == 0)
		return (ft_export(argc, argv));
	if (ft_strcmp(command, "env") == 0)
		return (ft_env(argc, argv));
	if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(argc, argv));
    if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(argc, argv));
	if (is_absolute_path(command))
		return (execute_absolute_command(command, argv));
	return (find_command_in_path(command, argv));
}
