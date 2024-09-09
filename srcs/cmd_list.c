/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:30:34 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/09 10:54:38 by jajuntti         ###   ########.fr       */
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

/*
int	cmd_print(t_cmd *cmd)
{
	int		i;
	int		arg_i;
	t_redir 	*infile;
	t_redir 	*outfile;

	i = 1;
	infile = NULL;
	outfile = NULL;
	printf("Printing commands!\n");
	while (cmd)
	{
		arg_i = 0;
		printf("Command %d contains the following:\n", i);
		if (cmd->cmd_arr)
		{
			while (cmd->cmd_arr[arg_i])
			{
				printf("	Arg %d = %s\n", arg_i, cmd->cmd_arr[arg_i]);
				arg_i++;
			}
		}
		infile = cmd->infiles;
		if (infile)
			printf("	Infile redirections are:\n");
		while (infile)
		{
			if (infile->flag)
				printf("		Heredoc with delimiter [%s]\n", infile->file_str);
			else
				printf("		File with path [%s]\n", infile->file_str);
			infile = infile->next;
		}
		outfile = cmd->outfiles;		
		if (outfile)
			printf("	Outfile redirections are:\n");
		while (outfile)
		{
			if (outfile->flag)
				printf("		Append file with path [%s]\n", outfile->file_str);
			else
				printf("		File with path [%s]\n", outfile->file_str);
			outfile = outfile->next;
		}
		i++;
		cmd = cmd->next;
	}
	return (0);
}
*/