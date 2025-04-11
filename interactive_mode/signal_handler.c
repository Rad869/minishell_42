/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramaros <cramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:38:32 by cramaros          #+#    #+#             */
/*   Updated: 2025/04/10 08:15:16 by cramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_general	*get_general_instance(void)
{
	static t_general	*instance;

	instance = NULL;
	return (instance);
}

void	handle_sigint(int sig, t_general *general)
{
	t_general	*general;

	general = get_general_instance();
	if (!general)
		return ;
	if (general->signal->child_pid == 0 && !general->signal->in_execution)
	{
		printf("\n");
		general->signal->exit_status = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (general->signal->child_pid != 0)
	{
		printf("\n");
		general->signal->exit_status = 130;
	}
	(void)sig;
}

void	handle_sigquit(int sig, t_general *general)
{
	t_general	*general;

	general = get_general_instance();
	if (!general)
		return ;
	if (general->signal->child_pid != 0)
	{
		printf("Quit: 3\n");
		general->signal->exit_status = 131;
	}
	(void)sig;
}

void	init_signals(t_general *general)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	get_general_instance() = general;
	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
	signal(SIGTERM, SIG_IGN);
}