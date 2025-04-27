/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:34:10 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/23 23:47:20 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(int argc, char **argv, t_general *ret)
{
	char	*current_directory;

	if (argc > 1)
	{
		if (argv[1] && argv[1][0] == '-')
		{
			write(2, "pwd: invalid option\n", 20);
			ret->last_exit_status = 2;
			return (1);
		}
	}
	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		perror("pwd");
		ret->last_exit_status = 1;
		return (1);
	}
	write(1, current_directory, ft_strlen(current_directory));
	write(1, "\n", 1);
	free(current_directory);
	ret->last_exit_status = 0;
	return (0);
}
