/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 06:01:25 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/26 22:30:24 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_entry(t_general *general)
{
	char	*entry;
	int		last;

	entry = NULL;
	general->heredoc_file_num = 0;
	dup2(general->default_fd[1], STDOUT_FILENO);
	dup2(general->default_fd[0], STDIN_FILENO);
	entry = readline("Minishell>");
	if (!entry)
	{
		last = general->last_exit_status;
		printf("exit\n");
		free_all(general);
		exit (last);
	}
	if (entry && entry[0] != 0)
		add_history(entry);
	if (!error_management(entry))
		return (free(entry), write(2, "Minishell: parse error\n", 23), 0);
	general->nbr_cmds = 0;
	general->args = get_list_args(entry);
	return (1);
}

int	get_len_word(char *line, int i)
{
	int	j;
	int	quote_index;

	j = 0;
	while (line[i + j] && line[i + j] != ' ' && !is_quote(line[i + j])
		&& !is_special(line + i + j))
		j++;
	if (is_quote(line[i + j]))
	{
		quote_index = i + j++;
		while (line[i + j] && line[i + j] != line[quote_index])
			j++;
		j++;
		j += get_len_word(line, i + j);
	}
	return (j);
}
