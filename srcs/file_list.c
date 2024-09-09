/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:14:19 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/09 10:54:38 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Creates a new file struct and initialises its file_str with the parameter sting. 

A pointer to the new_file is returned, unless there is a malloc error.
*/
t_redir	*redir_new(char *content, int type)
{
	t_redir	*new_file;

	new_file = malloc(sizeof(t_redir));
	if (!new_file)
		return (NULL);
	new_file->file_str = ft_strdup(content);
	if (!new_file->file_str)
	{
		free(new_file);
		return (NULL);
	}
	new_file->type = type;
	new_file->next = NULL;
	return (new_file);
}

/*
Adds the new_file to the end of the file_list. If file_list is empty to start 
with, file_list is set equal to the new_file.
*/
void	redir_add_back(t_redir **file_list, t_redir *new_file)
{
	t_redir	*temp;

	if (*file_list == NULL)
		*file_list = new_file;
	else
	{
		temp = *file_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_file;
	}
}

/*
Frees the contents of the given file struct and then frees the struct pointer.
*/
void	redir_delone(t_redir *file)
{
	if (file == NULL)
		return ;
	if (file->file_str)
		free(file->file_str);
	free(file);
	file = NULL;
}

/*
Frees all the files and their contents in a file_list.
*/
void	redir_clear(t_redir **file_list)
{
	t_redir	*next;

	if (file_list == NULL)
		return ;
	while (*file_list)
	{
		next = (*file_list)->next;
		redir_delone(*file_list);
		*file_list = next;
	}
}
