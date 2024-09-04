/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:00:35 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/04 12:59:27 by pikkak           ###   ########.fr       */
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
		data->error_msg = ft_strdup("Dup2 failed\n");
	close(data->o_stdin);
	close(data->o_stdout);
}

/*
Checks if a file is a directory.
If it is an infile, checks if it exists and has the right to read
if it is an outfile, checks if it has the rights to write,
if the file exists empties it and if not creates it.
*/

int	check_file(t_data *data, t_file *cur_file, int flag)
{
	if (is_directory(cur_file->file_str) == 1)
		return (data->error_msg = ft_strdup("Is a directory\n"), ERROR);
	if (flag == 1)
	{
		if (access(cur_file->file_str, F_OK) == -1)
			return (data->error_msg = ft_strdup("No such file or directory\n"), \
					ERROR);
		if (open(cur_file->file_str, O_RDONLY) == -1)
			return (data->error_msg = ft_strdup("Permission denied\n"), ERROR);
	}
	if (flag == 2)
	{
		if (cur_file->flag)
		{
			if (open(cur_file->file_str, O_WRONLY | O_CREAT, 0666) == -1)
				return (data->error_msg = ft_strdup("Permission denied\n"), \
						ERROR);
		}
		else
		{
			if (open(cur_file->file_str, \
				O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1)
				return (data->error_msg = ft_strdup("Permission denied\n"), \
						ERROR);
		}
	}
	return (SUCCESS);
}
