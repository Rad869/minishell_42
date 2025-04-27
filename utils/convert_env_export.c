/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:11:27 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 15:13:14 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	affect_value_env(t_env *env, char **value)
{
	t_env	*tmp;
	int		i;
	char	*chartmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			chartmp = ft_strjoin(tmp->name, "=");
			value[i] = ft_strjoin(chartmp, tmp->value);
			free(chartmp);
		}
		else
			value[i] = ft_strdup(tmp->name);
		i++;
		tmp = tmp->next;
	}
}

char	**convert_env_to_char_export(t_env *env)
{
	char	**value;
	int		i;
	t_env	*tmp;
	t_env	*tmp1;

	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp1 = tmp->next;
		i++;
		tmp = tmp1;
	}
	value = (char **) ft_calloc(i + 1, sizeof(char *));
	affect_value_env(env, value);
	return (value);
}
