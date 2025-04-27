/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrabeari <rrabeari@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:40 by rrabeari          #+#    #+#             */
/*   Updated: 2025/04/27 13:44:05 by rrabeari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler_main(int signum)
{
	t_general	*general;

	(void) signum;
	general = get_general();
	if (general->is_parent)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (general->no_child)
			rl_redisplay();
		general->last_exit_status = 130;
	}
}

int	signal_message(t_general *general, int sig)
{
	if (sig == SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	else if (sig == SIGSEGV)
		write(2, "Segmentation fault (core dumped)\n", 33);
	else if (sig == SIGBUS)
		write(2, "Bus error occurred (SIGBUS)\n", 28);
	if (general)
		general->last_exit_status = 128 + sig;
	return (128 + sig);
}

void	signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler_main;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		perror("signal");
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		perror("signal");
}
