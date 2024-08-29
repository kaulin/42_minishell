/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:13:37 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/29 15:01:22 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Creates a new var varuct and initialises key and value from parameter string. 
Returns a pointer to new, or NULL in the case of error.
*/
t_var	*var_new(char *str)
{
	t_var	*new;

	new = NULL;
	new->key = NULL;
	new->value = NULL;
	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->key = ft_substr(str, 0, ft_strchr(str, '=') - str);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_stdrup(ft_strchr(str, '=') + 1);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	new->alpha = new;
	new->a_next = NULL;
	return (new);
}

/*
Adds the new to the end of the var_list. If var_list is empty to 
start with, var_list is set equal to the new.
*/
void	var_add_back(t_var **var_list, t_var *new)
{
	t_var	*temp;

	if (*var_list == NULL)
		*var_list = new;
	else
	{
		temp = *var_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	var_add_to_alpha(*var_list, new);
}

/*
Frees the contents of the given var varuct and then frees the varuct pointer.
*/
void	var_delone(t_var *var)
{
	if (var == NULL)
		return ;
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
}

/*
Frees all the vars and their contents in a var_list.
*/
void	var_clear(t_var **var_list)
{
	t_var	*next;

	if (var_list == NULL)
		return ;
	while (*var_list)
	{
		next = (*var_list)->next;
		var_delone(*var_list);
		*var_list = next;
	}
}
