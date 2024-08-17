/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/17 12:53:31 by pikkak           ###   ########.fr       */
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
	- We have heredoc and infile. This might be a syntax error and we do not need to handle it?
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

static void	get_input(t_cmd *cur_cmd, t_data *data)//we need to find the delimiter
{
	char	*input;
	int		fd[2];
	char	*delim;
	
	delim = cur_cmd->infiles->file_str;
	if (pipe(fd) == -1)
		fail(666, "Pipe failed", data);
	while (1)
	{
		input = readline("> ");//Should we use this or get_new_line
		if (!input)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strncmp(input, delim, ft_strlen(delim)) == 0 && \
			(input[ft_strlen(delim)] == '\n' || input[ft_strlen(delim)] == 0))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd[1]);
		free(input);
	}
	close(fd[1]);
	cur_cmd->in_fd = fd[0];
}

static void	input_redirection(t_cmd *cur_cmd, t_data *data)
{
	t_file	*cur_file;
	
	cur_file = cur_cmd->infiles; 
	if (!cur_file->flag && cur_file->file_str)//infile redirection without heredoc, we open the infile to stdin
	{
		while (cur_file->next)//We check that the files exists.
		{
			if (access(cur_file->file_str, O_RDONLY) == -1)
				fail(1, "No such file or directory", data);
			cur_file = cur_file->next;
		}
		cur_cmd->in_fd = open(cur_file->file_str, O_RDONLY);
		if (cur_cmd->in_fd == -1 || dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)//we replace the stdin-fd with the file-fd. Can we check these in the same sentence?
			fail(1, "No such file or directory", data);
		close(cur_cmd->in_fd);	
	}
	else if (cur_file->flag && !cur_file->next->file_str)//heredoc flag without infile we read from terminal. Where do we save the input?
		get_input(cur_cmd, data);
//saattaa olla useampi heredoc ja infile
//	else if (cur_cmd->heredoc_flag && cur_cmd->infile)
//		fail(1, "This shell does not support combining < and << in the same command", data);
}

void	output_redirection(t_cmd *cur_cmd, t_data *data)
{
	t_file	*cur_file;
	
	cur_file = cur_cmd->outfiles; 
	if (!cur_file->flag && cur_file->file_str)//if there is outfile but no append flag. If we have several outfiles we empty their content and only use the last one
	{
		while (cur_file->next)//We check that the files exists. And create them if not. We also empty their contents with O_TRUNC. THIS NEEDS TO BE MOVED?
		{
			open(cur_file->file_str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			cur_file = cur_file->next;
		}
		cur_cmd->out_fd = open(cur_file->file_str, O_WRONLY | O_CREAT | O_RDWR, 0644);
		if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)
			fail(1, "Redirection failed", data);
		close(cur_cmd->out_fd);
	}
	else if (cur_file->flag && cur_file->file_str)//if there is append flag and outfile or name of outfile? we append into the end of the outfile
	{
		cur_cmd->out_fd = open(cur_file->file_str, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)
			fail(1, "Redirection failed", data);
		close(cur_cmd->out_fd);
	}
	else if  (cur_file->flag && !cur_file->file_str)//if there is a append flag but no outfile we have an error
		fail(1, "Error, append no file", data);
}

//Checks if there is a redirection and if it is in input or output.

void	check_redirection(t_data *data, t_cmd *cur_cmd)//what if this fails at some point, then the child wont close the pipe_ends?
{
	//printf("%s\n", cur_cmd->infiles->file_str);
	if (cur_cmd->infiles)//if there is a infile or heredoc we redirect input
		input_redirection(cur_cmd, data);
	if (cur_cmd->outfiles)//if there is a outfile or appends we redirect output
		output_redirection(cur_cmd, data);
}