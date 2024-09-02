/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:00:35 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/02 22:28:05 by pikkak           ###   ########.fr       */
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

int	check_file(t_data *data, char *file, int flag)
{
	if (is_directory(file) == 1)
		return (data->error_msg = ft_strdup("Is a directory\n"), ERROR);
	if (flag == 1)//input
	{
		if (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1) 
			return (data->error_msg = ft_strdup("Permissiggon denied\n"), ERROR);
	}
	if (flag == 2)//output
	{
		if (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1) 
			return (data->error_msg = ft_strdup("Permission denied\n"), ERROR);
	}
	return (SUCCESS);
}