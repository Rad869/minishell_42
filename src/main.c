/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:29:43 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/02 05:44:10 by rrabeari         ###   ########.fr       */
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

// int main(int argc, char *argv[], char **env)
// {
// 	(void) argc;
// 	(void) argv;
// 	char	**args;
// 	pid_t	pid;
// 	t_general	*general;

// 	general = init(env);
// 	while (1)
// 	{
// 		if (!get_entry(general))
// 			continue ;
// 		args = convert_list_to_char(general->args);
// 		put_full_path(&args[0], general);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			execve(args[0], args, env);
// 			printf("Command not found\n");
// 			double_free(args);
// 			free_list_args(&general->args);
// 			exit(127);
// 		}
// 		else
// 		{
// 			int	wstatus;
// 			wait(&wstatus);
// 			if (WIFEXITED(wstatus))
// 				printf("Exit status is %d\n", WEXITSTATUS(wstatus));
// 		}
// 		double_free(args);
// 		free_list_args(&general->args);
// 	}
// 	free(general);
// 	return (0);
// }
void	show_inside_pipe(t_pipe *pipe_list)
{
	t_list_args	*tmp;
	t_list_args	*tmp2;

	tmp = pipe_list->content;
	while (tmp)
	{
		tmp2 = tmp->next;
		printf("'%s '", tmp->content);
		tmp = tmp2;
	}
}

int main(int argc, char *argv[], char **env)
{
	t_general	*general;
	t_pipe		*tmp;
	t_pipe		*tmp2;
	(void) argc;
	(void) argv;

	general = init_general(env);
	if (!get_entry(general))
		return (free_env(general->env), free(general), 0);
	to_pipe(general);
	tmp = general->pipe_list;
	while (tmp)
	{
		tmp2 = tmp->next;
		show_inside_pipe(tmp);
		printf(" | ");
		tmp = tmp2;
	}
	printf("\n");
	free_env(general->env);
	free_pipe(&general->pipe_list);
	free(general);
	return (0);
}
