/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/17 20:05:11 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Situations
	- We do not have redirection
	- With builtins we have eg. echo/pwd/env testing > test.txt or cat << LIMIT
	IN
	- We have heredoc but no infile//we read from terminal
	- We have infile (redirection), we read from infile
	- We have heredoc and infile. This might be a syntax error and we do not need to handle it?
	OUT
	- We don't have outfile
	- We have outfile (redirection)
	- We have append but no outfile
	- We have append and outfile
*/

/*
Lets the user insert lines of input, until a line that contains only the 
delimiter string. A forced EoF is caught and an error is printed to STDERROR. 
Each line given is printed to the write end of the given pipe.

static void	get_input(t_piper **piper, char *delim, int *fd)
{
	char	*input;

	while ("true")
	{
		input = ft_get_next_line(STDIN_FILENO);
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
	(*piper)->in_fd = fd[0];
}*/

/*
void	input_redirection(t_cmd *cur_cmd)
{
	if (!cur_cmd->heredoc_flag && cur_cmd->infile)//infile redirection we open the infile to stdin.
	{
		cur_cmd->in_fd = open(cur_cmd->infile, O_RDONLY);//opens the file, do we need to add right checks etc?
		if (cur_cmd->in_fd == -1 || dup2(cur_cmd->in_fd, STDIN_FILENO);)//we replace the stdin-fd with the file-fd. Can we check these in the same sentence?
		{
			fail();
		}
		close(cur_cmd->in_fd);	
	}
	else if (cur_cmd->heredoc_flag && !cur_cmd->infile)//heredoc flag without infile we read from terminal
	{
		get_input();
	}
}

void	output_redirection(t_cmd *cur_cmd)
{

}

void	output_redirection(t_cmd *cur_cmd)
{
	if (cur_cmd->outfile != NULL && !cur_cmd->append_flag)//if there is outfile but no append flag
	{
		cur_cmd->out_fd = open(cur_cmd->outfile, O_WRONLY | O_CREAT | O_RDWR, 0644);
		if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO);)
		{
			fail();
		}
		close(cur_cmd->out_fd);
	}
	else if (cur_cmd->append_flag && cur_cmd->outfile)//if there is append flag and outfile or name of outfile? we append into the end of the outfile
	{
		cur_cmd->out_fd = open(cur_cmd->outfile, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO);)
		{
			fail();
		}
		close(cur_cmd->out_fd);
	}
	else if  (cur_cmd->append_flag && !cur_cmd->outfile)//if there is a append flag but no outfile we have an error
	{
		fail();
	}
	//what if there is both redirection and append flag?
}

/*
Checks if there is a redirection and if it is in input or output. Is data necessary?
*/
/*
void	check_redirection(t_data *data, t_cmd *cur_cmd)//what if this fails at some point, then the child wont close the pipe_ends? Do we need 
{
	if (cur_cmd->infile || cur_cmd->heredoc_flag)//if there is a infile or heredoc we redirect input
	{
		input_redirection(cur_cmd);
	}
	if (cur_cmd->outfile || cur_cmd->append_flag)//if there is a outfile or appends we redirect output
	{
		output_redirection(cur_cmd);
	}
}
*/

