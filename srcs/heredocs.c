/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:16:36 by pikkak            #+#    #+#             */
/*   Updated: 2024/09/03 22:23:03 by pikkak           ###   ########.fr       */
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
	char *input;
	
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

static int	get_input(t_cmd *cur_cmd, t_file *cur_file, t_data *data)
{
	int		fd[2];
	char	*delim;

	delim = cur_file->file_str;
	if (pipe(fd) == -1)
		return (data->error_msg = ft_strdup("Pipe failed\n"), ERROR);
	read_input(fd, delim);
	close(fd[1]);
	cur_cmd->in_fd = fd[0];
	return (SUCCESS);
}

int	check_heredocs(t_data *data, t_cmd *cur_cmd)
{
	t_file	*cur_file;
	int		heredoc_fd;

	cur_file = cur_cmd->infiles;//this is at the beginning of the files
	heredoc_fd = -1;
	while (cur_file)//go through the array and exec the heredocs
	{
		if (cur_file->flag)//if heredoc
		{
			if (get_input(cur_cmd, cur_file, data) != 0)//get input
				return (data->error_msg = ft_strdup("Error reading from heredoc\n"), ERROR);
			if (heredoc_fd != -1)
				close(heredoc_fd);
			heredoc_fd = cur_cmd->in_fd; // Track the latest heredoc's fd
		}
		cur_file = cur_file->next;
	}
	return (heredoc_fd);
}