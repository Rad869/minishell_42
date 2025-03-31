/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:35:34 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:23 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(int argc, char **argv)
{
	int	i;

	if (argc < 2)
	{
		write(2, "unset: missing argument\n", 24);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (unsetenv(argv[i]) == -1)
		{
			perror("unset");
			return (1);
		}
		i++;
	}
	return (0);
}
