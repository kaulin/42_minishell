/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:49:16 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/23 10:22:13 by pikkak           ###   ########.fr       */
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
		return (clean_return(cur_cmd->cmd_arr, NULL, 127));
	if (ft_strncmp(cur_cmd->cmd_arr[0], ".", 2) && is_directory(cur_cmd->path))
		return (clean_return(cur_cmd->cmd_arr, cur_cmd->path, 321));
	execve(cur_cmd->path, cur_cmd->cmd_arr, data->envp);
	return (clean_return(cur_cmd->cmd_arr, cur_cmd->path, 126));
}

/*
Child process handles input and output redirection as well and calls do_cmd to actually 
execute execve.*/

static void	child(t_data *data, t_cmd *cur_cmd, int *fd)
{
	int	err_code;

	close(fd[0]);
	if (cur_cmd-> next != NULL && dup2(fd[1], STDOUT_FILENO) == -1)// if it's not the last command
		fail(1, "Dup2 failed", NULL);
	close(fd[1]);
	//check_redirection(data, cur_cmd);// we do not need to give this the pipe, since this only handles the redirections inside the command. Should this be after builtin check?
	if (check_if_builtin(cur_cmd->cmd_arr) == 1)
	{
		execute_builtin(data, cur_cmd->cmd_arr);
		exit (0);
	}
		err_code = do_cmd(data, cur_cmd);
		if (err_code == 1)
			fail(err_code, "MSG", data);
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
		data->error_msg = ft_strdup("Pipe failed");
		return (ERROR);
	}
	cur_cmd->pid = fork();
	if (cur_cmd->pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		data->error_msg = ft_strdup("Fork failed");
		return (ERROR);
	}
	if (cur_cmd->pid == 0)
		child(data, cur_cmd, fd);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		data->error_msg = ft_strdup("Dup2 failed");
		return (ERROR);
	}
	close(fd[0]);
	return (0);
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
	data->o_stdin = dup(STDIN_FILENO);
	data->o_stdout = dup(STDOUT_FILENO);//where should these be, Make an extra function?
	if (cur_cmd->next == NULL && check_if_builtin(cur_cmd->cmd_arr) == 1)
	{
		//check_redirection(data, cur_cmd);
		return (execute_builtin(data, cur_cmd->cmd_arr));
	}
	else 
	{
		while (cur_cmd != NULL)
		{
			if (parent(data, cur_cmd) != 0)
			{
				wait_for_the_kids(data, cur_cmd);
				dup2(data->o_stdin, STDIN_FILENO);
				dup2(data->o_stdout, STDOUT_FILENO);
				close(data->o_stdin);
				close(data->o_stdout);
				//reset stdin & stdout, maybe a separate command for these
				return (ERROR);
			}
			cur_cmd = cur_cmd->next;
		}
	}
	if (wait_for_the_kids(data, cur_cmd))
		return (ERROR);
	dup2(data->o_stdin, STDIN_FILENO);
	dup2(data->o_stdout, STDOUT_FILENO);
	close(data->o_stdin);
	close(data->o_stdout);
	return (SUCCESS);
}


