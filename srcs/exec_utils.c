/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:00:35 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/02 22:51:22 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Resets the original in/out filedescriptors
*/
void	reset_io(t_data *data)
{
	if (dup2(data->o_stdin, STDIN_FILENO) == -1 || dup2(data->o_stdout, STDOUT_FILENO) == -1)
		data->error_msg = ft_strdup("Dup2 failed\n");
	close(data->o_stdin);
	close(data->o_stdout);
}

/*
Checks if a file is a directory.
If it is an infile, checks if it exists and has the right to read
if it is an outfile, checks if it has the rights to write, if the file exists empties it and if not creates it.
*/

int	check_file(t_data *data, char *file, int flag)
{
	if (is_directory(file) == 1)
		return (data->error_msg = ft_strdup("Is a directory\n"), ERROR);
	if (flag == 1)//input
	{
		if (access(file, F_OK) == -1)
			return (data->error_msg = ft_strdup("File doesn't exist\n"), ERROR);
		if (open(file, O_RDONLY) == -1) 
			return (data->error_msg = ft_strdup("Permission denied\n"), ERROR);
	}
	if (flag == 2)//output
	{
		if (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1) 
			return (data->error_msg = ft_strdup("Permission denied\n"), ERROR);
	}
	return (SUCCESS);
}
