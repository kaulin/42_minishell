/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/04 12:38:30 by pikkak           ###   ########.fr       */
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
		- If there are several infiles we need to go through them all and
		 return error if some of them don't exist. 
		- If they all exist we use the last one
		- If one of them doesn't exist we give error message
		"bash: not: No such file or directory"
	- We have heredoc but no infile//we read from terminal
	- We have heredoc and infile. We handle heredoc first
	and then the infiles. Does this change according to the order of the things?
	- We have several heredocs and/or infiles we handle heredocs first
	from left to right and then the infiles
	OUT
	- We have outfile (redirection)
	- We have serveral outfiles
		- If the files do not exist we create them and use the last one,
		by traversing a linked list and checking when files->next == NULL.
		If there is some content in the files we emty them.
	- We have append but no outfile
	- We have append and outfile
	- We have several appends/outfiles
		- The last outfile is the one that is used. Files before that are either
		emptied of content(redirection) or left as they are (append)
*/

/*
Goes through the infiles and checks that they exist,
have the correct rights and are not directories.
If the last file is an infile, closes the heredoc_fd and opens the file.
*/

static int	check_infiles(t_data *data, t_cmd *cur_cmd, int heredoc_fd)
{
	t_file	*cur_file;

	cur_file = cur_cmd->infiles;
	while (cur_file->next)
	{
		if (!cur_file->flag)
			if (check_file(data, cur_file, 1) == 1)
				return (ERROR);
		cur_file = cur_file->next;
	}
	if (!cur_file->flag)
	{
		if (heredoc_fd != -1)
			close(heredoc_fd);
		if (check_file(data, cur_file, 1) == 1)
			return (1);
		cur_cmd->in_fd = open(cur_file->file_str, O_RDONLY);
		if (dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)
			return (data->error_msg = ft_strdup("Dup failed\n"), ERROR);
		close(cur_cmd->in_fd);
	}
	return (SUCCESS);
}

static int	input_redirection(t_cmd *cur_cmd, t_data *data)
{
	int		heredoc_fd;

	heredoc_fd = check_heredocs(data, cur_cmd);
	if (heredoc_fd == 1)
		return (ERROR);
	if (check_infiles(data, cur_cmd, heredoc_fd) == 1)
		return (ERROR);
	while (cur_cmd->infiles->next)
		cur_cmd->infiles = cur_cmd->infiles->next;
	if (cur_cmd->infiles->flag && heredoc_fd != -1)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
			return (data->error_msg = ft_strdup("Dup failed\n"), ERROR);
		close(heredoc_fd);
	}
	return (SUCCESS);
}

static int	check_outfiles(t_data *data, t_file *cur_file)
{
	while (cur_file)
	{
		if (check_file(data, cur_file, 2) == 1)
			return (ERROR);
		cur_file = cur_file->next;
	}
	return (SUCCESS);
}

static int	output_redirection(t_cmd *cur_cmd, t_data *data)
{
	t_file	*cur_file;

	cur_file = cur_cmd->outfiles;
	if (cur_file->flag && !cur_file->file_str)
		return (data->error_msg = ft_strdup("Error, append no file\n"), ERROR);
	if (cur_file->file_str)
	{
		if (check_outfiles(data, cur_file) == 1)
			return (ERROR);
		while (cur_file->next)
			cur_file = cur_file->next;
		if (cur_file->flag)
			cur_cmd->out_fd = open(cur_file->file_str, \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			cur_cmd->out_fd = open(cur_file->file_str, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cur_cmd->out_fd == -1)
			return (data->error_msg = ft_strdup("Permission denied\n"), ERROR);
		if (cur_cmd->cmd_arr && dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)
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
