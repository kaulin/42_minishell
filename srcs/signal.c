/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:43:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/10 22:35:58 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handle ctrl-C, ctrl-D and ctrl
ctrl-C displays a new prompt on a new line.
ctrl-D exits the shell.
ctrl-\ does nothing.
Termios handles is used for handling terminal I/O (input/output) settings.
Tcgetattr() gets the terminal attributes(initializes the handler)
Tcsetattr sets attributes of the terminal associated with STDIN,
using the values stored in handler.
*/

void child_signal_handler(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_SUCCESS);
}

void signal_handler(int sig)
{
	if (in_heredoc)
	{
		if (sig == SIGINT)//doesn't go here when the signal comes from the child process
		{
			in_heredoc = 0;
			close(STDIN_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
	else
	{
		if (sig == SIGINT)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void setup_signal_handling(t_data *data, void (*handler)(int))
{
	struct sigaction sa;

	if (!handler)
		sa.sa_handler = signal_handler;
	else
		sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGINT, &sa, NULL);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		oops(data, 1, NULL, "sigaction failed");
}



