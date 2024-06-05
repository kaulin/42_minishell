/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:13:37 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/05 12:24:49 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
Creates a new str struct and initialises its str with the parameter sting. 
A pointer to the new_str is returned, unless there is a malloc error.
*/
t_str	*str_new(char *content)
{
	t_str	*new_str;

	new_str = malloc(sizeof(t_str));
	if (!new_str)
		return (NULL);
	new_str->str = content;
	new_str->next = NULL;
	return (new_str);
}

/*
Adds the new_str to the end of the str_list. If str_list is empty to 
start with, str_list is set equal to the new_str.
*/
void	str_add_back(t_str **str_list, t_str *new_str)
{
	t_str	*temp;

	if (*str_list == NULL)
		*str_list = new_str;
	else
	{
		temp = *str_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_str;
	}
}

/*
Frees the contents of the given str struct and then frees the struct pointer.
*/
void	str_delone(t_str *str)
{
	if (str == NULL)
		return ;
	if (str->str)
		free(str->str);
	free(str);
}

/*
Frees all the strs and their contents in a str_list.
*/
void	str_clear(t_str **str_list)
{
	t_str	*next;

	if (str_list == NULL)
		return ;
	while (*str_list)
	{
		next = (*str_list)->next;
		str_delone(*str_list);
		*str_list = next;
	}
}

/*
Merges the contents of all the str nodes into one string.
*/
char	*str_merge(t_str *str_list)
{
	char	*merged_string;
	char	*temp;

	merged_string = ft_strdup("");
	if (!merged_string)
		return (NULL);
	while (str_list)
	{
		temp = ft_strjoin(merged_string, str_list->str);
		free (merged_string);
		if (!temp)
			return (NULL);
		merged_string = temp;
		str_list = str_list->next;
	}
	return (merged_string);
}
