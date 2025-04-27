/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:43 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/25 22:12:55 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	double_free(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

static int	get_entry_main(t_general *g)
{
	if (!get_entry(g))
	{
		g->last_exit_status = 2;
		free_data(g);
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[], char **env)
{
	t_general	*general;

	(void) argv;
	general = init_general(env);
	while (argc)
	{
		general->no_child = 1;
		if (!get_entry_main(general))
			continue ;
		if (to_pipe(general) == 130)
		{
			free_data(general);
			continue ;
		}
		if (general->pipe_list)
		{
			exec_command(general);
			delete_all_tmp(general);
			free_data(general);
		}
	}
	free_all(general);
	return (0);
}
