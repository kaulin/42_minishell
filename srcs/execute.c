/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:49:16 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/21 14:33:53 by jajuntti         ###   ########.fr       */
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
execute execve.
*/
static void	child(t_data *data, t_cmd *cur_cmd, int *fd)
{
	int	err_code;
	
	if (cur_cmd != data->cmd_list)// If this is not the first command, we need to read from the pipe
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			close(fd[0]);
			close(fd[1]);
			fail(1, "Dup2 failed", data);
		}
	}
	if (cur_cmd->next != NULL)// If this is not the last command, we need to write to the pipe
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			close(fd[0]);
			close(fd[1]);
			fail(1, "Dup2 failed", data);
		}
	}
	close(fd[0]);
	close(fd[1]);
	//check_redirection(data, cur_cmd);// we do not need to give this the pipe, since this only handles the redirections inside the command. Should this be after builtin check?
	if (check_if_builtin(cur_cmd->cmd_arr) == 1)
		execute_builtin(data, cur_cmd->cmd_arr);
	else
	{
		err_code = do_cmd(data, cur_cmd);
		if (err_code == 1)//if do_cmd fails
			fail(42, "MSG", data);
	}
}

static void	parent(t_data *data, t_cmd *cur_cmd)
{
	int	fd[2];

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
		child(data, cur_cmd, fd);
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
	int		exit_status;
	int		status;
	t_cmd	*cur_cmd;

	exit_status = 0;
	cur_cmd = data->cmd_list;
	data->o_stdin = dup(STDIN_FILENO);
	data->o_stdout = dup(STDOUT_FILENO);//where should these be?
	//cur_cmd->cmd_arr = ft_split(cur_cmd->cmd_str, " ");
	if (cur_cmd->next == NULL && check_if_builtin(cur_cmd->cmd_arr) == 1)//The only case in which we do not fork is if there is only one command and it's a builtin
	{
		//check_redirection(data, cur_cmd);
		execute_builtin(data, cur_cmd->cmd_arr);
		return (exit_status);
	}
	else 
	{	
		while (cur_cmd != NULL)//we call the parent as many times a there are commands
		{
			//cur_cmd->cmd_arr = ft_split(cur_cmd->cmd_str, " ");
			parent(data, cur_cmd);
			cur_cmd = cur_cmd->next;
		}
		cur_cmd = data->cmd_list;
		while (cur_cmd != NULL)//this fails for some reason when we mix builtins with normal commands. Builtin return values?
		{
			if (waitpid(cur_cmd->pid, &status, 0) == -1)
			fail(1, "Waitpid failed", data);
			if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
			cur_cmd = cur_cmd->next;
		}
	}
	dup2(data->o_stdin, STDIN_FILENO);
	dup2(data->o_stdout, STDOUT_FILENO);
	close(data->o_stdin);
	close(data->o_stdout);
	return (exit_status);
}

/*
static void	parent(t_data *data, t_cmd *cur_cmd)
{
	int		fd[2];

	while (cur_cmd != NULL)
	{
		cur_cmd->cmd_arr = ft_split(cur_cmd->cmd_str, " ");
		if (pipe(fd) == -1)//make the pipe
			fail(666, "Pipe failed", data);
		cur_cmd->pid = fork();//make the child
		if (cur_cmd->pid == -1)
		{
			close(fd[0]);
			close(fd[1]);
			fail(666, "Fork failed", data);
		}
		if (cur_cmd->pid == 0)
			child(data, cur_cmd, fd);
		cur_cmd = cur_cmd->next;
	}
	close(fd[1]);//parent closes write end
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		fail(666, "Dup2 failed", data);
	}
	close(fd[0]);
}*/

