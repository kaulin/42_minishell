/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:00:35 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/17 23:21:22 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
