/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:30:34 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/21 15:11:48 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Creates a new cmd struct and initialises its cmd_str with the parameter sting. 
A pointer to the new_cmd is returned, unless there is a malloc 
*/
t_cmd	*cmd_new(char *content)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_str = content;
	new_cmd->next = NULL;
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
	if (cmd->cmd_str)
		free(cmd->cmd_str);
	free(cmd);
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