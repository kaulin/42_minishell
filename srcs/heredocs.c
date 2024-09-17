/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:16:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/09/17 14:59:41 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Reads input, until delimiter'
Each line is printed to the write end of the pipe.
If SIGINT is caught a signal handler is called and function stops reading input.
A forced EoF is caught and an error is printed to STDERROR.
*/

static void	read_input(int *fd, char *delim)
{
	char	*input;

	signal(SIGINT, heredoc_handler);
	while (1)
	{
		input = readline("> ");
		if (g_signal)
			break ;
		if (!input)
		{
			printf("warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strncmp(input, delim, ft_strlen(delim)) == 0 && \
			(input[ft_strlen(delim)] == '\n' || input[ft_strlen(delim)] == 0))
			break ;
		ft_putstr_fd(input, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(input);
	}
	signal(SIGINT, basic_handler);
	if (input)
		free(input);
}

static int	get_input(t_data *data, t_cmd *cmd, t_redir *redir)
{
	int		fd[2];
	char	*delim;

	delim = redir->file_str;
	if (dup2(data->o_stdin, STDIN_FILENO) == -1)
		return (oops(data, 1, NULL, "dup2 failed\n"));
	if (pipe(fd) == -1)
		return (oops(data, 1, NULL, "pipe failed\n"));
	read_input(fd, delim);
	close(fd[1]);
	if (g_signal)
	{
		if (cmd->heredoc_fd != -1)
			close(cmd->heredoc_fd);
		close(fd[0]);
		data->status = 130;
		if (dup2(data->o_stdin, STDIN_FILENO) == -1)
			return (oops(data, 1, NULL, "dup2 failed\n"));
		return (-1);
	}
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	cmd->heredoc_fd = fd[0];
	return (SUCCESS);
}

int	check_heredocs(t_data *data, t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (get_input(data, cmd, redir) == 1)
					return (oops(data, 1, NULL, \
					"Error reading from heredoc\n"));
				if (g_signal)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
