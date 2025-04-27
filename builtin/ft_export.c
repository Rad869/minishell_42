/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:35:13 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/27 01:14:50 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	print_env(t_general *ret)
{
	int		i;
	char	**env;

	i = 0;
	env = convert_env_to_char(ret->env);
	while (env[i])
		printf("export %s\n", env[i++]);
	ret->last_exit_status = 0;
	double_free(env);
	return (0);
}

static int	handle_export_error(char *var, t_general *ret, int *set)
{
	write(2, "export: '", 9);
	write(2, var, ft_strlen(var));
	write(2, "' : Invalid identifier\n", 23);
	if (*set)
	{
		ret->last_exit_status = 1;
		*set = 0;
	}
	return (1);
}

static int	process_export_var(char *arg, t_general *ret, int set)
{
	t_env	*tmp;
	t_env	*tmp1;
	char	*name;
	char	*value;

	tmp = ret->env;
	name = get_env_name(arg);
	value = get_env_value(arg);
	while (tmp && ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	if (tmp)
		return (free(tmp->value), tmp->value = value, free(name), 0);
	tmp = ret->env;
	while (tmp->next)
		tmp = tmp->next;
	tmp1 = (t_env *) malloc(sizeof(t_env));
	tmp1->name = name;
	tmp1->value = value;
	tmp1->next = NULL;
	tmp->next = tmp1;
	if (set)
		ret->last_exit_status = 0;
	return (0);
}

static int	is_valid_identifier(const char *str)
{
	if (!str || !*str || ft_isdigit(*str) || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	ft_export(int argc, char **argv, t_general *ret)
{
	char	**env;
	int		i;
	int		set;

	env = convert_env_to_char_export(ret->env);
	i = 1;
	set = 1;
	if (argc == i)
		return (double_free(env), print_env(ret));
	while (i < argc)
	{
		if (argv[1] && argv[1][0] == '-' && argv[1][1] != 0)
			return (double_free(env), ret->last_exit_status = 2,
				invalid_option_mess("export", argv[1]), 1);
		if (!is_valid_identifier(argv[i]))
			ret->last_exit_status = handle_export_error(argv[i], ret, &set);
		else
			process_export_var(argv[i], ret, set);
		i++;
	}
	return (double_free(env), 0);
}
