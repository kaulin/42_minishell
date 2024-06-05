/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:49:16 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/05 19:28:33 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(int *fd, t_data *data, t_cmd *cur_cmd)
{


}

static void	parent(t_data *data, t_cmd *cur_cmd)
{
	int		fd[2];

	if (pipe(fd) == -1)
		fail(666, "Pipe failed", data);
	cur_cmd->pid = fork();
	if (cur_cmd->pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		fail(666, "Fork failed", data);
	}
	if (cur_cmd->pid == 0)
		child(fd, data, cur_cmd);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		fail(666, "Dup2 failed", data);
	}
	close(fd[0]);
}

/*
Goes through the linked list and calls the parent function for each node (cmd) of the list. Then waits for all the children to finish
*/

int	execute_and_pipe(t_data *data)
{
	int		i;
	int		exit_status;
	int		status;
	t_cmd	*cur_cmd;

	i = 0;
	cur_cmd = data->cmd_list;
	while (cur_cmd != NULL)
	{
		parent(data, cur_cmd);
		cur_cmd = cur_cmd->next;
	}
	cur_cmd = data->cmd_list;
	while (cur_cmd != NULL)
	{
		exit_status = 0;
		if (waitpid(cur_cmd->pid, status, 0) == -1)
			fail(1, "Waitpid failed", data);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		cur_cmd = cur_cmd->next;
	}
}