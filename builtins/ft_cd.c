/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:33:35 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:11 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	cd_path(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd(int argc, char **argv)
{
	if (argc == 1)
		return (cd_home());
	if (argc == 2)
		return (cd_path(argv[1]));
	write(2, "cd: too many arguments\n", 23);
	return (1);
}
