/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:43:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/11 12:12:23 by kkauhane         ###   ########.fr       */
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

/*
Handler for parent.
Ignores SIGINT during child process execution.
*/
void	parent_signal_handler(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_IGN);
}

/*
Handler for child process.
Exits child in case of SIGINT.
*/
void	child_signal_handler(int sig)
{
	(void)sig;
	exit(130);
}

/*
Handler for SIGINT during heredoc.
Sets heredoc to 2 and closes STDIN to stop readline from reading.
*/
void	hd_signal_handler(int sig)
{
	(void)sig;
	if (g_in_heredoc)
	{
		g_in_heredoc = 2;
		close(STDIN_FILENO);
	}
}

/*
Handler for SIGUSR1.
Handles heredoc interruption by SIGINT as it should.
Sets in_heredoc at 0 again.
*/
void	sigusr1_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_in_heredoc = 0;
}

/*
Basic handler for SIGINT
*/
void	basic_signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
