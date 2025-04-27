/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:33:35 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/27 14:11:53 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_env_pwd(t_general *general)
{
	char	*current_dir;
	t_env	*env;
	t_env	*tmp;

	current_dir = getcwd(NULL, 0);
	env = general->env;
	while (env->next && ft_strcmp(env->name, "PWD") != 0)
		env = env->next;
	if (env && ft_strcmp(env->name, "PWD") == 0)
	{
		free(env->value);
		env->value = current_dir;
	}
	else
	{
		tmp = (t_env *) ft_calloc(1, sizeof(t_env));
		tmp->name = ft_strdup("PWD");
		tmp->value = current_dir;
		tmp->next = NULL;
		env->next = tmp;
	}
}

static void	change_env_old_pwd(t_general *general, char *old)
{
	t_env	*env;
	t_env	*tmp;

	env = general->env;
	while (env->next && ft_strcmp(env->name, "OLDPWD") != 0)
		env = env->next;
	if (env && ft_strcmp(env->name, "OLDPWD") == 0)
	{
		free(env->value);
		env->value = old;
	}
	else
	{
		tmp = (t_env *) ft_calloc(1, sizeof(t_env));
		tmp->name = ft_strdup("OLDPWD");
		tmp->value = old;
		tmp->next = NULL;
		env->next = tmp;
	}
}

static int	cd_home(t_general *ret)
{
	char	*home;
	char	*old;

	home = getenv("HOME");
	old = getcwd(NULL, 0);
	if (home == NULL)
	{
		write(2, "Error\n", 6);
		write(2, "cd: HOME not set\n", 17);
		ret->last_exit_status = 1;
		free(old);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		ret->last_exit_status = 1;
		free(old);
		return (1);
	}
	change_env_pwd(ret);
	change_env_old_pwd(ret, old);
	ret->last_exit_status = 0;
	return (0);
}

static int	cd_path(char *path, t_general *ret)
{
	char	*old;

	old = getcwd(NULL, 0);
	if (path && path[0] == '-' && path[1] != 0)
		return (free(old), invalid_option_mess("cd", path), 1);
	if (chdir(path) == -1)
	{
		perror("cd");
		ret->last_exit_status = 1;
		free(old);
		return (1);
	}
	change_env_pwd(ret);
	change_env_old_pwd(ret, old);
	ret->last_exit_status = 0;
	return (0);
}

int	ft_cd(int argc, char **argv, t_general *ret)
{
	if (argc == 1)
		return (cd_home(ret));
	if (argc == 2)
		return (cd_path(argv[1], ret));
	write(2, "Error\n", 6);
	write(2, "cd: too many argument\n", 23);
	ret->last_exit_status = 1;
	return (1);
}
