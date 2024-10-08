/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:49:16 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/19 12:02:45 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
If command not found from environment paths, tries to use the command itself as
path. Calls execve with given path and command array and environment.
*/
static int	do_cmd(t_data *data, t_cmd *cur_cmd)
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
	signal(SIGINT, child_handler);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	if (check_redir(data, cur_cmd) || !cur_cmd->cmd_arr)
		close_clean_exit(data, fd[1], cur_cmd->out_fd);
	if (cur_cmd-> next != NULL && dup2(fd[1], STDOUT_FILENO) == -1)
	{
		oops(data, 1, NULL, "dup2 failed");
		close_clean_exit(data, fd[1], cur_cmd->out_fd);
	}
	close(fd[1]);
	if (cur_cmd->out_fd != -1)
	{
		if (dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)
		{
			oops(data, 1, NULL, "dup2 failed");
			close_clean_exit(data, -1, cur_cmd->out_fd);
		}
		close(cur_cmd->out_fd);
	}
	if (check_if_builtin(cur_cmd->cmd_arr))
		exec_builtin(data, cur_cmd->cmd_arr);
	else
		do_cmd(data, cur_cmd);
	exit(clean_data(data, 1));
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
	if (cur_cmd->pid == 0)
		child(data, cur_cmd, fd);
	if (cur_cmd->cmd_arr && ft_strncmp(cur_cmd->cmd_arr[0], "./minishell", 11))
		signal(SIGQUIT, child_quitter);
	signal(SIGINT, parent_handler);
	close(fd[1]);
	if (cur_cmd->heredoc_fd != -1)
		close(cur_cmd->heredoc_fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		return (oops(data, ERROR, NULL, "dup2 failed"));
	}
	return (close(fd[0]));
}

/*
Goes through the linked list and calls the parent function for each node (cmd) 
of the list. Then waits for all the children to finish
*/
static int	go_through_cmds(t_data *data, t_cmd *cur_cmd)
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
	if (wait_for_the_kids(data, cur_cmd))
		return (ERROR);
	reset_io(data);
	return (SUCCESS);
}

/*
Gets paths, checks heredocs and g_signal and calls go_through()
*/
int	execute_and_pipe(t_data *data)
{
	t_cmd	*cur_cmd;

	cur_cmd = data->cmd_list;
	get_paths(data);
	if (check_heredocs(data, data->cmd_list) == ERROR)
		return (reset_io(data), ERROR);
	if (g_signal)
		return (-1);
	if (cur_cmd->next == NULL && check_if_builtin(cur_cmd->cmd_arr) == 1)
	{
		if (check_redir(data, cur_cmd) > 0 || dup_builtin(data, cur_cmd) \
			|| exec_builtin(data, cur_cmd->cmd_arr))
			return (reset_io(data), ERROR);
		reset_io(data);
		return (SUCCESS);
	}
	return (go_through_cmds(data, cur_cmd));
}
