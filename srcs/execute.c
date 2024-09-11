/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:49:16 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/11 11:46:36 by kkauhane         ###   ########.fr       */
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
	if (!cur_cmd->path && access(cur_cmd->cmd_arr[0], F_OK) == 0 \
		&& ft_strchr(cur_cmd->cmd_arr[0], '/'))
	{
		cur_cmd->path = ft_strdup(cur_cmd->cmd_arr[0]);
		free(cur_cmd->cmd_arr[0]);
		cur_cmd->cmd_arr[0] = ft_strdup(ft_strrchr(cur_cmd->path, '/') + 1);
	}
	if (!cur_cmd->path)
		return (oops(data, 127, cur_cmd->cmd_arr[0], NULL));
	if (is_directory(cur_cmd->path))
		return (oops(data, 126, cur_cmd->path, "Is a directory"));
	execve(cur_cmd->path, cur_cmd->cmd_arr, data->envp_arr);
	return (oops(data, 126, cur_cmd->path, NULL));
}

/*
Child process handles input and output redirection as well and calls do_cmd to 
actually execute execve.
*/
static void	child(t_data *data, t_cmd *cur_cmd, int *fd)
{
	close(fd[0]);
	if (check_redir(data, cur_cmd) || !cur_cmd->cmd_arr)
	{
		close(fd[1]);
		exit(data->status);
	}
	if (g_in_heredoc == 2)
	{
		kill(getppid(), SIGUSR1);
		exit (data->status);
	}
	setup_signal_handling(data, child_signal_handler);
	if (cur_cmd-> next != NULL && dup2(fd[1], STDOUT_FILENO) == -1)
		exit(oops(data, 1, NULL, "dup2 failed"));
	close(fd[1]);
	if (cur_cmd->out_fd != -1 && dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)
	{
		exit(oops(data, 1, NULL, "dup2 failed"));
		close(cur_cmd->out_fd);
	}
	if (check_if_builtin(cur_cmd->cmd_arr))
		exec_builtin(data, cur_cmd->cmd_arr);
	else
		do_cmd(data, cur_cmd);
	clean_data(data);
	exit(data->status);
}

/*
Makes the pipe and forks the children. Returns -1 if there is no cmd->array 
for cur_cmd.
*/
static int	parent(t_data *data, t_cmd *cur_cmd)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (oops(data, ERROR, NULL, "pipe failed"));
	cur_cmd->pid = fork();
	if (cur_cmd->pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (oops(data, ERROR, NULL, "fork failed"));
	}
	setup_signal_handling(data, parent_signal_handler);
	if (cur_cmd->pid == 0)
		child(data, cur_cmd, fd);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		return (oops(data, ERROR, NULL, "dup2 failed"));
	}
	close(fd[0]);
	return (SUCCESS);
}

int	wait_for_the_kids(t_data *data, t_cmd *failed_cmd)
{
	t_cmd	*cur_cmd;
	int		status;

	cur_cmd = data->cmd_list;
	while (cur_cmd != failed_cmd && cur_cmd->pid)
	{
		if (waitpid(cur_cmd->pid, &status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
			else
				return (oops(data, ERROR, NULL, "waitpid failed"));
		}
		if (WIFEXITED(status))
			data->status = WEXITSTATUS(status);
		cur_cmd = cur_cmd->next;
	}
	return (SUCCESS);
}

/*
Goes through the linked list and calls the parent function for each node (cmd) 
of the list. Then waits for all the children to finish
*/
int	execute_and_pipe(t_data *data)
{
	t_cmd	*cur_cmd;

	cur_cmd = data->cmd_list;
	get_paths(data);
	if (cur_cmd->next == NULL && check_if_builtin(cur_cmd->cmd_arr) == 1)
	{
		if (check_redir(data, cur_cmd) || exec_builtin(data, cur_cmd->cmd_arr))
			return (reset_io(data), ERROR);
	}
	else
	{
		while (cur_cmd != NULL)
		{
			if (parent(data, cur_cmd) > 0)
			{
				wait_for_the_kids(data, cur_cmd);
				return (reset_io(data), ERROR);
			}
			cur_cmd = cur_cmd->next;
		}
	}
	if (wait_for_the_kids(data, cur_cmd))
		return (ERROR);
	reset_io(data);
	return (SUCCESS);
}
