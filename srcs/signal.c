/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:43:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/12 13:44:55 by kkauhane         ###   ########.fr       */
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

void	handle_parent(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_parent_heredoc(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(STDIN_FILENO);
	g_signal = 42;
}

void	handle_child_heredoc(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	close(STDIN_FILENO);
	exit(130);
}

void	handle_child(void)
{
	exit(130);
}

/*
Handler for SIGINT during heredoc.
Sets heredoc to 2 and closes STDIN to stop readline from reading.
*/
void	signal_handler(int sig)
{
	(void)sig;
	if (g_signal == 0)
		handle_parent();
	if (g_signal == 1)
		handle_parent_heredoc();
	else if (g_signal == 2)
		handle_child();
	else if (g_signal == 3)
		handle_child_heredoc();
}
