/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:39:45 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:31 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute_path(const char *command)
{
	return (command != NULL && command[0] == '/');
}

int	execute_absolute_command(const char *command, char *argv[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (pid == 0)
	{
		execv(command, argv);
		perror("execv failed");
		exit(1);
	}
	else
		wait(NULL);
	return (0);
}

void	build_full_path(const char *dir, const char *command, char *full_path)
{
	full_path[0] = '\0';
	ft_strncat(full_path, dir, MAX_PATH_LENGTH - 1);
	if (ft_strlen(full_path) + 1 < MAX_PATH_LENGTH)
	{
		ft_strncat(full_path, "/", MAX_PATH_LENGTH
			- ft_strlen(full_path) - 1);
	}
	if (ft_strlen(full_path) + ft_strlen(command) + 1 < MAX_PATH_LENGTH)
	{
		ft_strncat(full_path, command, MAX_PATH_LENGTH
			- ft_strlen(full_path) - 1);
	}
}

int	search_directory(const char *dir, const char *command, char *argv[])
{
	DIR		*dp;
	struct dirent	*entry;

	dp = opendir(dir);
	if (!dp)
		return (-1);
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, command) == 0)
		{
			closedir(dp);
			return (check_and_execute(dir, command, argv));
		}
		entry = readdir(dp);
	}
	closedir(dp);
	return (-1);
}

static int	check_and_execute(const char *dir, const char *command,
	char *argv[])
{
	char	full_path[MAX_PATH_LENGTH];

	full_path[MAX_PATH_LENGTH] = {0};
	if (ft_strlen(dir) + ft_strlen(command) + 2 > MAX_PATH_LENGTH)
		return (-1);
	ft_strcat(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, command);
	if (access(full_path, X_OK) == 0)
		return (execute_absolute_command(full_path, argv));
	return (-1);
}
