/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:13:37 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/06 13:13:17 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Creates a new var varuct and initialises key and value from parameter strings. 
Returns a pointer to new, or NULL in the case of error.
*/
t_var	*var_new(char *key, char *value)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->alpha = new;
	new->anext = NULL;
	return (new);
}

/*
Adds the new to the end of the var_list. If var_list is empty to 
start with, var_list is set equal to the new. The alphabetic pointer list 
is also updated accordingly.
*/
void	var_add_back(t_var **var_list, t_var *new)
{
	t_var	*temp;

	if (*var_list == NULL)
		*var_list = new;
	else
	{
		temp = *var_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		var_add_to_alpha(*var_list, new);
	}
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

/*
Returns a heap allocated string of the var's contents in the format 
key=value.
*/
char	*var_to_str(t_var *var)
{
	char	*temp;
	char	*final;

	temp = NULL;
	final = NULL;
	temp = ft_strjoin(var->key, "=");
	if (!temp)
		return (NULL);
	final = ft_strjoin(temp, var->value);
	free(temp);
	return (final);
}
