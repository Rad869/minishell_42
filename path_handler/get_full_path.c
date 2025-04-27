/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:45:02 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/24 00:14:30 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_in_directory(char *dir_arg, char *cmd)
{
	DIR				*dir;
	struct dirent	*elements;

	dir = opendir(dir_arg);
	if (dir == NULL)
		return (0);
	elements = readdir(dir);
	while (elements != NULL)
	{
		if (elements->d_type != DT_DIR \
			&& ft_strncmp(elements->d_name, cmd, 100) == 0)
		{
			closedir(dir);
			return (1);
		}
		elements = readdir(dir);
	}
	closedir(dir);
	return (0);
}

char	*get_full_p(char *env_path, char *cmd)
{
	char	*value;
	char	*value2;
	char	**env_path_list;
	int		i;

	value = NULL;
	i = 0;
	if (env_path == NULL)
		return (cmd);
	env_path_list = ft_split(env_path, ':');
	while (env_path_list[i] != NULL)
	{
		if (is_in_directory(env_path_list[i], cmd))
		{
			value = ft_strjoin(env_path_list[i], "/");
			value2 = ft_strjoin(value, cmd);
			double_free(env_path_list);
			free(value);
			return (value2);
		}
		i++;
	}
	double_free(env_path_list);
	return (cmd);
}
