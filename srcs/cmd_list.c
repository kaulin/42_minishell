/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:30:34 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/17 15:00:44 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Creates a new cmd struct and initialises its cmd_str with the parameter sting. 
A pointer to the new_cmd is returned, unless there is a malloc 
*/
t_cmd	*cmd_new(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_arr = NULL;
	new_cmd->path = NULL;
	new_cmd->redirects = NULL;
	new_cmd->in_fd = -1;
	new_cmd->out_fd = -1;
	new_cmd->heredoc_fd = -1;
	new_cmd->next = NULL;
	new_cmd->pid = 0;
	return (new_cmd);
}

/*
Adds the new_cmd to the end of the cmd_list. If cmd_list is empty to start with, 
cmd_list is set equal to the new_cmd.
*/
void	cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		temp = *cmd_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

/*
Frees the contents of the given cmd struct and then frees the struct pointer.
*/
void	cmd_delone(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->path)
		free(cmd->path);
	if (cmd->cmd_arr)
		clean_array(cmd->cmd_arr);
	if (cmd->redirects)
		redir_clear(&cmd->redirects);
	free(cmd);
	cmd = NULL;
}

/*
Frees all the cmds and their contents in a cmd_list.
*/
void	cmd_clear(t_cmd **cmd_list)
{
	t_cmd	*next;

	if (cmd_list == NULL)
		return ;
	while (*cmd_list)
	{
		next = (*cmd_list)->next;
		cmd_delone(*cmd_list);
		*cmd_list = next;
	}
}
