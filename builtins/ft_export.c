/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:35:13 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:18 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(int argc, char **argv)
{
	extern char	**env;
	int			i;

	i = 0;
	if (argc == 1)
	{
		while (env[i])
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	else
	{
		if (setenv(argv[1], argv[2], 1) == -1)
		{
			perror("export");
			return (1);
		}
	}
	return (0);
}
