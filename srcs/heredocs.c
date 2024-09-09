/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:16:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/09/09 13:29:15 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Lets the user insert lines of input, until a line that contains only the 
delimiter string. A forced EoF is caught and an error is printed to STDERROR. 
Each line given is printed to the write end of the given pipe.
*/
static void	read_input(int *fd, char *delim)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strncmp(input, delim, ft_strlen(delim)) == 0 && \
			(input[ft_strlen(delim)] == '\n' || input[ft_strlen(delim)] == 0))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(input);
	}
}

static int	get_input(t_cmd *cur_cmd, t_redir *cur_file, t_data *data)
{
	int		fd[2];
	char	*delim;

	delim = cur_file->file_str;
	if (dup2(data->o_stdin, STDIN_FILENO) == -1)
		return (oops(data, 1, NULL, "dup2 failed\n"));
	if (pipe(fd) == -1)
		return (oops(data, 1, NULL, "pipe failed\n"));
	read_input(fd, delim);
	close(fd[1]);
	cur_cmd->in_fd = fd[0];
	return (SUCCESS);
}

int	check_heredocs(t_data *data, t_cmd *cur_cmd)
{
	t_redir	*cur_file;
	int		heredoc_fd;

	cur_file = cur_cmd->redirects;
	heredoc_fd = -1;
	while (cur_file)
	{
		if (cur_file->type == HEREDOC)
		{
			if (get_input(cur_cmd, cur_file, data) != 0)
				return (oops(data, 1, NULL, "Error reading from heredoc\n"));
			if (heredoc_fd != -1)
				close(heredoc_fd);
			heredoc_fd = cur_cmd->in_fd;
		}
		cur_file = cur_file->next;
	}
	return (heredoc_fd);
}
