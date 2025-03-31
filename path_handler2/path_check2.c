/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:08:31 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:33 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_command_in_path(const char *command, char *argv[])
{
	char	*path;
	char	path_copy[MAX_PATH_LENGTH];
	char	*dir;

	path = getenv("PATH");
	if (path == NULL)
	{
		printf("Error: PATH is not defined.\n");
		return (-1);
	}
	path_copy[MAX_PATH_LENGTH];
	ft_strncpy(path_copy, path, MAX_PATH_LENGTH);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		if (search_directory(dir, command, argv) == 0)
			return (0);
		dir = strtok(NULL, ":");
	}
	printf("Error: command not found: %s\n", command);
	return (-1);
}
