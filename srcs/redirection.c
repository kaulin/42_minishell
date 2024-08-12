/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/12 11:18:36 by kkauhane         ###   ########.fr       */
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
	
	delim = cur_cmd->cmd_arr[2];//Is this correct? Does the command array include redirections?
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
	int i;

	i = 1;//where is the first redirection in the array?
	if (!cur_cmd->heredoc_flag && cur_cmd->infile)//infile redirection we open the infile to stdin
	{
		while (cur_cmd->cmd_arr[i])//We check that the files exists. Can we just go through the array like this? What does it contain?
		{
			if (access(cur_cmd->cmd_arr[i], O_RDONLY) == -1)
				fail(1, "No such file or directory", data);
			i++;
		}
		cur_cmd->in_fd = open(cur_cmd->infile, O_RDONLY);
		if (cur_cmd->in_fd == -1 || dup2(cur_cmd->in_fd, STDIN_FILENO))//we replace the stdin-fd with the file-fd. Can we check these in the same sentence?
			fail(1, "No such file or directory", data);
		close(cur_cmd->in_fd);	
	}
	else if (cur_cmd->heredoc_flag && !cur_cmd->infile)//heredoc flag without infile we read from terminal
		get_input(cur_cmd, data);
	else if (cur_cmd->heredoc_flag && cur_cmd->infile)
		fail(1, "This shell does not support combining < and << in the same command", data);
}

void	output_redirection(t_cmd *cur_cmd, t_data *data)
{
	//int i;

	//i = 1;
	if (cur_cmd->outfile != NULL && !cur_cmd->append_flag)//if there is outfile but no append flag. If we have several outfiles we empty their content and only use the last one
	{
		cur_cmd->out_fd = open(cur_cmd->outfile, O_WRONLY | O_CREAT | O_RDWR, 0644);
		if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO))
		{
			fail(1, "Error", data);
		}
		close(cur_cmd->out_fd);
	}
	else if (cur_cmd->append_flag && cur_cmd->outfile)//if there is append flag and outfile or name of outfile? we append into the end of the outfile
	{
		cur_cmd->out_fd = open(cur_cmd->outfile, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO))
		{
			fail(1, "Error", data);
		}
		close(cur_cmd->out_fd);
	}
	else if  (cur_cmd->append_flag && !cur_cmd->outfile)//if there is a append flag but no outfile we have an error
	{
		fail(1, "Error", data);
	}
}

//Checks if there is a redirection and if it is in input or output.

void	check_redirection(t_data *data, t_cmd *cur_cmd)//what if this fails at some point, then the child wont close the pipe_ends? Do we need 
{
	if (cur_cmd->infile || cur_cmd->heredoc_flag)//if there is a infile or heredoc we redirect input
	{
		input_redirection(cur_cmd, data);
	}
	if (cur_cmd->outfile || cur_cmd->append_flag)//if there is a outfile or appends we redirect output
	{
		output_redirection(cur_cmd, data);
	}
}