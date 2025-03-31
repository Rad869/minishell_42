/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:34:10 by cramaros          #+#    #+#             */
/*   Updated: 2025/03/29 08:38:21 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char	*current_directory;

	(void) argc;
	(void) argv;
	current_directory = getcwd(NULL, 0);
	if (current_directory == NULL)
	{
		perror("pwd");
		return (1);
	}
	write(1, current_directory, ft_strlen(current_directory));
	write(1, "\n", 1);
	free(current_directory);
	return (0);
}
