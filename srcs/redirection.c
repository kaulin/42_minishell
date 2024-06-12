/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/12 15:02:24 by kkauhane         ###   ########.fr       */
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
void	input_redirection(t_cmd *cur_cmd)
{
	if (cur_cmd->heredoc_flag && !cur_cmd->infile)//heredoc flag without infile we read from terminal
		cur_cmd->in_fd = STDIN_FILENO;
	if (!cur_cmd->heredoc_flag && cur_cmd->infile)//infile redirection we open the infile to stdin.
		cur_cmd->in_fd = open(cur_cmd->infile, O_RDONLY);
	if (cur_cmd->in_fd == -1 || dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)//if there was an error in opening the file or with replacing the fd 1 with the file fd
		fail("bash: syntax error near unexpected token `newline'");
	//close(cur_cmd->in_fd);
}

void	output_redirection(t_cmd *cur_cmd)
{
	if (cur_cmd->append_flag && cur_cmd->outfile)//if there is append flag and outfile or name of outfile? we append into the end of the outfile
		cur_cmd->out_fd = open(cur_cmd->outfile, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (cur_cmd->append_flag && !cur_cmd->outfile)//if there is heredoc but no outfile we have error, do we need this?
		fail();
	else
		cur_cmd->out_fd = open(cur_cmd->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);//if there is no heredoc but outfile
	if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)//if there was an error in opening the file or with replacing the fd 0 with the file fd
		fail();
	//close(cur_cmd->out_fd);
}

void	check_redirection(t_data *data, t_cmd *cur_cmd)
{
	if (cur_cmd->infile || cur_cmd->heredoc_flag)//if there is a infile or heredoc we redirect input
	{
		input_redirection(cur_cmd);
	}
	if (cur_cmd->outfile || cur_cmd->append_flag)//if there is a outfile or appens we redirect output
	{
		output_redirection(cur_cmd);
	}
}*/