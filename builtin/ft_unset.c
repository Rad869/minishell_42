/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:35:34 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/26 18:27:48 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	invalid_option_mess(char *cmd, char *opt)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, opt, ft_strlen(opt));
	write(2, ": invalid option\n", 17);
	get_general()->last_exit_status = 2;
}

static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] == '-' && str[1] != 0)
		return (invalid_option_mess("unset", str), 0);
	while (!str[0] || str[i])
	{
		if (!str || !str[0] || ft_isdigit(str[0])
			|| (!ft_isalpha(str[0]) && str[0] != '_')
			|| (!ft_isalnum(str[i]) && str[i] != '_'))
		{
			write (2, "unset: '", 8);
			write(2, str, ft_strlen(str));
			write(2, "': not a valid identifier\n", 26);
			get_general()->last_exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	free_and_delete(t_env *env, t_env *tmp0)
{
	t_env	*tmp1;

	tmp1 = env->next;
	if (env)
	{
		free(env->name);
		free(env->value);
		free(env);
		if (!tmp0)
			get_general()->env = tmp1;
		else
			tmp0->next = tmp1;
	}
}

static int	valid_check_free(char *name, char *argv, t_env *tmp, t_env *tmp0)
{
	if (!is_valid_identifier(argv))
		return (0);
	if (ft_strcmp(name, argv) == 0)
	{
		free_and_delete(tmp, tmp0);
		return (0);
	}
	return (1);
}

int	ft_unset(int argc, char **argv, t_general *ret)
{
	t_env	*tmp0;
	t_env	*tmp;
	int		i;

	i = 1;
	ret->last_exit_status = 0;
	if (argc <= i)
		return (ret->last_exit_status = 0, 0);
	tmp = ret->env;
	tmp0 = NULL;
	while (i < argc)
	{
		tmp = ret->env;
		while (tmp)
		{
			if (!valid_check_free(tmp->name, argv[i], tmp, tmp0))
				break ;
			tmp0 = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (ret->last_exit_status);
}
