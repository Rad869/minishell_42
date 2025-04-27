/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_args_to_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 02:00:34 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 15:18:17 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	affect_value(t_list_args *args, char **value)
{
	t_list_args	*tmp;
	t_list_args	*tmp2;
	int			i;

	tmp = args;
	i = 0;
	while (tmp)
	{
		tmp2 = tmp->next;
		value[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp2;
	}
}

char	**convert_list_to_char(t_list_args *args)
{
	char		**value;
	int			i;
	t_list_args	*tmp;
	t_list_args	*tmp2;

	tmp = args;
	i = 0;
	while (tmp)
	{
		tmp2 = tmp->next;
		i++;
		tmp = tmp2;
	}
	value = (char **) ft_calloc(i + 1, sizeof(char *));
	affect_value(args, value);
	return (value);
}

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
			i++;
		}
		tmp = tmp->next;
	}
}

char	**convert_env_to_char(t_env *env)
{
	char	**value;
	int		i;
	t_env	*tmp;

	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
			i++;
		tmp = tmp->next;
	}
	value = (char **) ft_calloc(i + 1, sizeof(char *));
	affect_value_env(env, value);
	return (value);
}
