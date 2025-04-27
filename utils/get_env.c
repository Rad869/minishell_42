/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:47:09 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/18 07:00:01 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_name(char *line)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (line[i])
	{
		if (line[i] == '=')
			break ;
		i++;
	}
	name = (char *) malloc(sizeof(char) * (i + 2));
	ft_strlcpy(name, line, i + 1);
	return (name);
}

char	*get_env_value(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			break ;
		i++;
	}
	if (i != (int)ft_strlen(line))
		return (ft_strdup(line + i + 1));
	return (NULL);
}

t_env	*get_env(char **env)
{
	int		i;
	t_env	*env_return;
	t_env	*tmp;

	i = 0;
	env_return = (t_env *) malloc(sizeof(t_env));
	tmp = env_return;
	while (env[i + 1])
	{
		tmp->name = get_env_name(env[i]);
		tmp->value = get_env_value(env[i]);
		tmp->next = (t_env *) malloc(sizeof(t_env));
		tmp = tmp->next;
		i++;
	}
	tmp->name = get_env_name(env[i]);
	tmp->value = get_env_value(env[i]);
	tmp->next = NULL;
	return (env_return);
}

char	*get_path(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (ft_strncmp("PATH", tmp->name, 4) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp2;
	}
	return (NULL);
}
