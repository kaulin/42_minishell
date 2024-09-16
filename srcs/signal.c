/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:43:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/16 14:52:44 by jajuntti         ###   ########.fr       */
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

void	basic_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	close(STDIN_FILENO);
}

void	parent_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	child_handler(int sig)
{
	(void)sig;
	exit(130);
}
