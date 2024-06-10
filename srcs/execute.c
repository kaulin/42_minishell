/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:49:16 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/10 14:32:50 by kkauhane         ###   ########.fr       */
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
Scenarios:
- First command:
	- We have heredoc but no infile//we reed from terminal
	- We have infile (redirection), we read from infile
	- We have heredoc and infile. This might be a syntax error and we do not need to handle it?
	- We don't have redirection
- Last command:
	- We don't have outfile
	- We have outfile (redirection)
	- We have heredoc but no outfile
	- We have heredoc and outfile
*/
static void	open_dub_close(t_data *data, t_cmd *cur_cmd)
{
	if (data->cmd_list == cur_cmd)//we check if the command is the very first
	{
		if (cur_cmd->heredoc_flag && !cur_cmd->infile) //heredoc flag but no infile do we need this?
			cur_cmd->in_fd = STDIN_FILENO;
		if (!cur_cmd->heredoc_flag && cur_cmd->infile)//redirection we open the infile to stdin.
			cur_cmd->in_fd = open(cur_cmd->infile, O_RDONLY);
		if (cur_cmd->in_fd == -1 || dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)//if there was an error in opening the file or with replacing the fd 1 with the file fd
			fail("bash: syntax error near unexpected token `newline'");
		close(cur_cmd->in_fd);
	}
	if (cur_cmd->next == NULL)//if it is the last command
	{
		if (cur_cmd->append_flag && cur_cmd->outfile)//if there is append flag and outfile we append into the end of the outfile
			cur_cmd->out_fd = open(cur_cmd->outfile, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (cur_cmd->append_flag && !cur_cmd->outfile)//if there is heredoc but no outfile we have error, do we need this?
			fail();
		else
			cur_cmd->out_fd = open(cur_cmd->outfile, O_TRUNC | O_CREAT | O_RDWR, 0644);//if there is no heredoc but outfile
		if (cur_cmd->out_fd == -1 || dup2(cur_cmd->out_fd, STDOUT_FILENO) == -1)//if there was an error in opening the file or with replacing the fd 0 with the file fd
			fail();
		close(cur_cmd->out_fd);
	}
}

/*
Child process handles input and output redirection and calls do_cmd to actually 
execute execve.
*/

static void	child(int *fd, t_data *data, t_cmd *cur_cmd)
{
	int	err_code;

	close(fd[0]);
	if (cur_cmd-> next != NULL && dup2(fd[1], STDOUT_FILENO) == -1)//checks that the current command is not the last
		//fail(1, "Dup2 failed", data);
	close(fd[1]);
	//if (*((*piper)->cmdv[(*piper)->cmd_i]) == 0) //checks if the cmd is empty. Do we need this? Is this not checked in the parsing stage?
		//fail(127, (*piper)->cmdv[(*piper)->cmd_i], piper);
	open_dub_close(data, cur_cmd);
	err_code = do_cmd(data, cur_cmd);
	//if (err_code == 1)
		//fail(err_code, "Memory allocation error", piper);
	//if ((*piper)->cmd_err)
		//fail(err_code, (*piper)->cmd_err, piper);
	//fail(err_code, (*piper)->cmdv[(*piper)->cmd_i], piper);
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