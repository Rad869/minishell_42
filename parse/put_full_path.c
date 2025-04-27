/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:45:54 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/24 10:00:31 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_full_path(char **cmd, t_general *general)
{
	t_env	*env;
	char	*value;
	char	*path;

	env = general->env;
	path = get_path(env);
	value = get_full_p(path, *cmd);
	if (*cmd && ft_strncmp(value, *cmd, ft_strlen(*cmd)) != 0)
	{
		free (*cmd);
		*cmd = NULL;
		*cmd = value;
	}
	free(path);
}
