/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/09 13:27:57 by jajuntti         ###   ########.fr       */
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

static int	redirect_input(t_data *data, t_cmd *cur_cmd, t_redir *redir, int heredoc_fd)
{
	if (redir->type == HEREDOC)
		cur_cmd->in_fd = heredoc_fd;
	else
	{
		if (heredoc_fd != -1)
			close(heredoc_fd);
		cur_cmd->in_fd = open(redir->file_str, O_RDONLY);
		if (dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)
			return (oops(data, 1, NULL, "dup2 failed\n"));
		close(cur_cmd->in_fd);
	}
	return (SUCCESS);
}

static int	redirect_output(t_data *data, t_cmd *cur_cmd, t_redir *redir)
{
	if (redir->type == APPEND)
		cur_cmd->out_fd = open(redir->file_str, \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		cur_cmd->out_fd = open(redir->file_str, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cur_cmd->out_fd == -1)
		return (oops(data, 1, redir->file_str, "Permission denied"));
	if (cur_cmd->cmd_arr && dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)
		return (oops(data, 1, NULL, "dup2 failed"), ERROR);
	close(cur_cmd->out_fd);
	return (SUCCESS);
}

/*
Checks if there is a redirection and if it is in input or output.
*/
int	check_redir(t_data *data, t_cmd *cur_cmd)
{
	t_redir	*redir;
	t_redir	*last_in;
	t_redir	*last_out;
	int		heredoc_fd;


	last_in = NULL;
	last_out = NULL;
	heredoc_fd = check_heredocs(data, cur_cmd);
	if (heredoc_fd )
	redir = cur_cmd->redirects;
	while (redir)
	{
		if (check_file(data, redir))
			return (ERROR);
		if (redir->type == INFILE || redir->type == HEREDOC)
			last_in = redir;
		else if (redir->type == OUTFILE || redir->type == APPEND)
			last_out = redir;
		redir = redir->next;
	}
	if (last_in && redirect_input(data, cur_cmd, last_in, heredoc_fd))
			return (ERROR);
	if (last_out && redirect_output(data, cur_cmd, last_out))
			return (ERROR);
	return (SUCCESS);
}
