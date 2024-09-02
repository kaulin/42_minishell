/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/02 23:17:09 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Situations
	- We do not have redirection
	- With builtins we have eg. echo/pwd/env testing > test.txt or cat << LIMIT
	IN
	- We have infile (redirection), we read from infile
	- We have several redirections/infiles
		- If there are several infiles we need to go through them all and return error if some of them don't exist. 
		- If they all exist we use the last one
		- If one of them doesn't exist we give error message "bash: not: No such file or directory"
	- We have heredoc but no infile//we read from terminal
	- We have heredoc and infile. We handle heredoc first and then the infiles. Does this change according to the order of the things?
	- We have several heredocs and/or infiles we handle heredocs first from left to right and then the infiles
	OUT
	- We have outfile (redirection)
	- We have serveral outfiles
		- If the files do not exist we create them and use the last one, by traversing a linked list and checking when files->next == NULL. If there is some content in the files we emty them.
	- We have append but no outfile
	- We have append and outfile
	- We have several appends/outfiles
		- The last outfile is the one that is used. Files before that are either emptied of content(redirection) or left as they are (append)
*/

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

static int	get_input(t_cmd *cur_cmd, t_data *data)
{
	int		fd[2];
	char	*delim;

	delim = cur_cmd->infiles->file_str;
	if (pipe(fd) == -1)
		return (data->error_msg = ft_strdup("Pipe failed\n"), ERROR);
	read_input(fd, delim);
	close(fd[1]);
	cur_cmd->in_fd = fd[0];
	if (dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)
	{
		close(cur_cmd->in_fd);
		return (data->error_msg = ft_strdup("dup2 failed\n"), ERROR);
	}
	close(cur_cmd->in_fd);
	return (SUCCESS);
}

static int	input_redirection(t_cmd *cur_cmd, t_data *data)
{
	t_file	*cur_file;
	
	cur_file = cur_cmd->infiles;
	if (cur_file->file_str)
	{
		while (cur_file->next)//go through the array and exec the heredocs
		{
			if (cur_file->flag)
				if (get_input(cur_cmd, data) != 0)
					return (data->error_msg = ft_strdup("Error reading from heredoc\n"), ERROR);
			cur_file = cur_file->next;
		}
		if (cur_file->flag)//if the last one is heredoc
			if (get_input(cur_cmd, data) != 0)
				return (data->error_msg = ft_strdup("Error reading from heredoc\n"), ERROR);
		cur_file = cur_cmd->infiles;
		while (cur_file->next)//go thought the array and check the files
		{
			if (!cur_file->flag)
				if (check_file(data, cur_file->file_str, 1) == 1)
					return (1);
			cur_file = cur_file->next;
		}
		if (!cur_file->flag)// if the last one is a file
		{
			if (check_file(data, cur_file->file_str, 1) == 1)
				return (1);
			cur_cmd->in_fd = open(cur_file->file_str, O_RDONLY);
			if (dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)
				return (data->error_msg = ft_strdup("Dup failed\n"), ERROR);
			close(cur_cmd->in_fd);
		}
	}
	return (SUCCESS);
}
/*
static int	input_redirection(t_cmd *cur_cmd, t_data *data)
{
	t_file	*cur_file;
	
	cur_file = cur_cmd->infiles;
	if (cur_file->flag)
		if (get_input(cur_cmd, data) != 0)
			return (data->error_msg = ft_strdup("Error reading from heredoc\n"), ERROR);
	if (!cur_file->flag && cur_file->file_str)
	{
		while (cur_file->next)
		{
			if (check_file(data, cur_file->file_str, 1) == 1)
				return (1);
			cur_file = cur_file->next;
		}
		if (check_file(data, cur_file->file_str, 1) == 1)
			return (1);
		cur_cmd->in_fd = open(cur_file->file_str, O_RDONLY);
		if (dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)
			return (data->error_msg = ft_strdup("Dup failed\n"), ERROR);
		close(cur_cmd->in_fd);
	}
	return (SUCCESS);
}*/

static int	output_redirection(t_cmd *cur_cmd, t_data *data)
{
	t_file	*cur_file;
	
	cur_file = cur_cmd->outfiles;
	if  (cur_file->flag && !cur_file->file_str)
		return (data->error_msg = ft_strdup("Error, append no file\n"), ERROR);
	if (cur_file->file_str)
	{
		while (cur_file->next)
		{
			if (check_file(data, cur_file->file_str, 1) == 1)
				return (1);
			cur_file = cur_file->next;
		}
		if (check_file(data, cur_file->file_str, 0) == 1)
			return (1);
		if (cur_file->flag)
			cur_cmd->out_fd = open(cur_file->file_str,  O_WRONLY | O_APPEND | O_CREAT, 0644);
		else 
			cur_cmd->out_fd = open(cur_file->file_str,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cur_cmd->out_fd == -1)
			return (data->error_msg = ft_strdup("Permission denied\n"), ERROR);
		if (dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)
			return (data->error_msg = ft_strdup("Dup2 error\n"), ERROR);
		close(cur_cmd->out_fd);
	}
	return (SUCCESS);
}

/*
Checks if there is a redirection and if it is in input or output.
*/

int	check_redirection(t_data *data, t_cmd *cur_cmd)
{
	if (cur_cmd->infiles)
		if (input_redirection(cur_cmd, data) != 0)
			return (ERROR);
	if (cur_cmd->outfiles)
		return (output_redirection(cur_cmd, data));
	return (SUCCESS);
}