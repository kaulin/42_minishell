/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:43:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/18 17:27:31 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handle ctrl-C, ctrl-D and ctrl
ctrl-C displays a new prompt on a new line.
ctrl-D exits the shell.
ctrl-\ does nothing.
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

void	child_quitter(int sig)
{
	(void)sig;
	g_signal = 1;
	write(2, "Quit (core dumped)", 18);
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	child_handler(int sig)
{
	exit(sig);
}
