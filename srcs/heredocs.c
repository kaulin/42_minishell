/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:16:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/09/13 14:27:11 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Reads input, until delimiter'
Each line is printed to the write end of the pipe.
If SIGINT is caught a signal handler is called and function stops reading input.
A forced EoF is caught and an error is printed to STDERROR.
*/

static void	read_input(t_data *data, int *fd, char *delim)
{
	char	*input;

	signal(SIGINT, heredoc_handler);
	while (1)
	{
		input = readline("> ");
		if (g_signal)
			break;
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
	}
	if (input)
		free(input);
	if (data->parent_process)
		signal(SIGINT, basic_handler);
	else
		signal(SIGINT, child_handler);
}

static int	get_input(t_data *data, t_cmd *cur_cmd, t_redir *redir)
{
	int		fd[2];
	char	*delim;

	delim = redir->file_str;
	if (dup2(data->o_stdin, STDIN_FILENO) == -1)
		return (oops(data, 1, NULL, "dup2 failed\n"));
	if (pipe(fd) == -1)
		return (oops(data, 1, NULL, "pipe failed\n"));
	read_input(data, fd, delim);
	close(fd[1]);
	cur_cmd->in_fd = fd[0];
	return (SUCCESS);
}

int	check_heredocs(t_data *data, t_cmd *cur_cmd, int *heredoc_fd)
{
	t_redir	*redir;

	redir = cur_cmd->redirects;
	*heredoc_fd = -1;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (get_input(data, cur_cmd, redir) == 1)
				return (oops(data, 1, NULL, "Error reading from heredoc\n"));
			if (g_signal)
			{
				data->status = 130;
				if (data->parent_process)
					break;
				clean_data(data);
				exit (130);
			}
			if (*heredoc_fd != -1)
				close(*heredoc_fd);
			*heredoc_fd = cur_cmd->in_fd;
		}
		redir = redir->next;
	}
	return (SUCCESS);
}
