/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:39:08 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 18:41:46 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	access_output(char *filename)
{
	struct stat	file;

	if (!access(filename, F_OK))
	{
		if (access(filename, W_OK))
		{
			write(2, filename, ft_strlen(filename));
			write(2, ": Permission denied\n", 20);
			get_general()->last_exit_status = 1;
			return (0);
		}
	}
	if (lstat(filename, &file) == 0)
	{
		if (S_ISDIR(file.st_mode))
		{
			write(2, filename, ft_strlen(filename));
			write(2, ": Is a directory\n", 17);
			get_general()->last_exit_status = 1;
			return (0);
		}
	}
	return (1);
}
