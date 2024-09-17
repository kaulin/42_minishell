/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:00:35 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/17 23:52:31 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_the_kids(t_data *data, t_cmd *failed_cmd)
{
	t_cmd	*cur_cmd;
	int		status;

	cur_cmd = data->cmd_list;
	status = 0;
	while (cur_cmd != failed_cmd && cur_cmd->pid)
	{
		if (cur_cmd->pid)
		{
			if (waitpid(cur_cmd->pid, &status, 0) == -1)
			{
				if (errno != EINTR)
					return (oops(data, ERROR, NULL, "waitpid failed"));
			}
			if (WIFEXITED(status))
				data->status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				data->status = status + 128;
		}
		cur_cmd = cur_cmd->next;
	}
	return (SUCCESS);
}

/*
Resets the original in/out filedescriptors
*/
void	reset_io(t_data *data)
{
	if (dup2(data->o_stdin, STDIN_FILENO) == -1 || \
		dup2(data->o_stdout, STDOUT_FILENO) == -1)
		oops(data, 1, NULL, "dup2 failed");
}

/*
Checks if a file is a directory.
If it is an infile, checks if it exists and has the right to read
if it is an outfile, checks if it has the rights to write,
if the file exists empties it and if not creates it.
*/
int	check_file(t_data *data, t_redir *redir)
{
	if (is_directory(redir->file_str) == 1)
		return (oops(data, 1, redir->file_str, "Is a directory"));
	if (redir->type == INFILE && access(redir->file_str, F_OK) == -1)
		return (oops(data, 1, redir->file_str, "No such file or directory"));
	if (redir->type == INFILE && open(redir->file_str, O_RDONLY) == -1)
		return (oops(data, 1, redir->file_str, "Permission denied"));
	if (redir->type == APPEND)
	{
		if (open(redir->file_str, O_WRONLY | O_CREAT, 0666) == -1)
			return (oops(data, 1, redir->file_str, "Permission denied"));
	}
	else if (redir->type == OUTFILE)
	{
		if (open(redir->file_str, \
			O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1)
			return (oops(data, 1, redir->file_str, "Permission denied"));
	}
	return (SUCCESS);
}
