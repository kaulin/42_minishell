/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:49:16 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/30 13:35:12 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
If command not found from environment paths, tries to use the command itself as
path. Calls execve with given path and command array and environment.
*/
int	do_cmd(t_data *data, t_cmd *cur_cmd)
{
	cur_cmd->path = find_cmd_path(data, cur_cmd->cmd_arr[0]);
	if (!cur_cmd->path && access(cur_cmd->cmd_arr[0], F_OK) == 0 && ft_strchr(cur_cmd->cmd_arr[0], '/'))
	{
		cur_cmd->path = ft_strdup(cur_cmd->cmd_arr[0]);
		free(cur_cmd->cmd_arr[0]);
		cur_cmd->cmd_arr[0] = ft_strdup(ft_strrchr(cur_cmd->path, '/') + 1);
	}
	if (!cur_cmd->path)
		return (127);
	if (ft_strncmp(cur_cmd->cmd_arr[0], ".", 2) && is_directory(cur_cmd->path))
		return (321);
	execve(cur_cmd->path, cur_cmd->cmd_arr, data->envp_arr);
	return (126);
}

/*
Child process handles input and output redirection as well and calls do_cmd to actually 
execute execve.*/
static void	child(t_data *data, t_cmd *cur_cmd, int *fd)
{
	int	err_code;

	close(fd[0]);
	if (cur_cmd-> next != NULL && dup2(fd[1], STDOUT_FILENO) == -1)// if it's not the last command we make it write its output to the next one
		fail(1, "Dup2 failed\n", NULL);
	close(fd[1]);
	check_redirection(data, cur_cmd);
	if (check_if_builtin(cur_cmd->cmd_arr) == 1)
	{
		execute_builtin(data, cur_cmd->cmd_arr);
		exit (0);
	}
	else
	{	
		err_code = do_cmd(data, cur_cmd);
		if (err_code != 0)
			fail(err_code, "Error", data);
	}
}

/*
Makes the pipe and forks the children. 
Waits for the children to finish and sets the pipeline for the next command
*/
static int	parent(t_data *data, t_cmd *cur_cmd)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		data->error_msg = ft_strdup("Pipe failed\n");
		return (ERROR);
	}
	cur_cmd->pid = fork();
	if (cur_cmd->pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (data->error_msg = ft_strdup("Fork failed\n"), ERROR);
	}
	if (cur_cmd->pid == 0)
		child(data, cur_cmd, fd);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		return (data->error_msg = ft_strdup("Dup2 failed\n"), ERROR);
	}
	close(fd[0]);
	return (SUCCESS);
}

int	wait_for_the_kids(t_data *data, t_cmd *failed_cmd)
{
	t_cmd	*cur_cmd;
	int		status;

	cur_cmd = data->cmd_list;
	while (cur_cmd != failed_cmd)
	{
		if (waitpid(cur_cmd->pid, &status, 0) == -1)
		{
			data->error_msg = ft_strdup("Waitpid failed\n");
			return (ERROR);
		}
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
		cur_cmd = cur_cmd->next;
	}
	return (SUCCESS);
}

/*
Goes through the linked list and calls the parent function for each node (cmd) of the list. Then waits for all the children to finish
*/
//add find_path to this function

int	execute_and_pipe(t_data *data)
{
	t_cmd	*cur_cmd;

	cur_cmd = data->cmd_list;
	if (cur_cmd->next == NULL && check_if_builtin(cur_cmd->cmd_arr) == 1)
	{
		if (check_redirection(data, cur_cmd) == 1 || execute_builtin(data, cur_cmd->cmd_arr) == 1)
			return (reset_io(data), ERROR);
	}
	else 
	{
		while (cur_cmd != NULL)
		{
			if (parent(data, cur_cmd) != 0)
			{
				wait_for_the_kids(data, cur_cmd);
				reset_io(data);
				return (ERROR);
			}
			cur_cmd = cur_cmd->next;
		}
	}
	if (wait_for_the_kids(data, cur_cmd))
		return (ERROR);
	reset_io(data);
	return (SUCCESS);
}


