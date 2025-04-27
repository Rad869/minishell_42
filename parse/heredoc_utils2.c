/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:19:48 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/27 12:03:41 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	null_heredoc(char *line, int fd)
{
	if (line == NULL)
	{
		close(fd);
		rl_on_new_line();
		rl_replace_line("", 0);
		write(2, "warning: here-document should terminated by delimitor\n", 54);
		return (1);
	}
	return (0);
}

int	loop_heredoc(int fd, char *delimiter, int f)
{
	char	*line;
	int		state;

	state = 1;
	while (state != 0)
	{
		line = readline(">");
		if (null_heredoc(line, fd))
			return (1);
		state = ft_strcmp(line, delimiter);
		expande_heredoc(&line, get_general(), f);
		if (state != 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free (line);
	}
	return (0);
}

static char	*heredoc_name(void)
{
	char		*name;
	t_general	*g;

	g = get_general();
	name = ft_itoa(g->heredoc_file_num);
	while (access(name, F_OK) == 0)
	{
		(g->heredoc_file_num)++;
		free(name);
		name = NULL;
		name = ft_itoa(g->heredoc_file_num);
	}
	return (name);
}

void	affect_heredoc_name(t_pipe *pip)
{
	t_pipe		*tmp;

	tmp = pip;
	while (tmp)
	{
		if (tmp->heredoc_list)
			tmp->heredoc_file = heredoc_name();
		tmp = tmp->next;
	}
}
