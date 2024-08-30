/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_edits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:42:39 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/30 16:01:05 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_set_key_and_value(char *str, char **key, char **value)
{
	*value = NULL;
	if (ft_strchr(str, '='))
	{
		*key = ft_substr(str, 0, ft_strchr(str, '=') - str);
		if (!*key)
			return (ERROR);
		*value = ft_strdup(ft_strchr(str, '=') + 1);
		if (!*value)
		{
			free(*key);
			return (ERROR);
		}
	}
	else
	{
		*key = ft_strdup(str);
		if (!key)
			return (ERROR);
		*value = NULL;
	}
	return (SUCCESS);
}

/*
If the key from the given string matches an existing var in the var_list, 
updates that var's value with the value from the given string. Otherwise 
creates a new var with the given string and adds it to var_list.
*/
int	var_add_var(t_var **var_list, char *str)
{
	t_var	*var;
	char	*key;
	char	*value;

	if (var_set_key_and_value(str, &key, &value))
		return (ERROR);
	var = var_get_var(*var_list, key);
	if (var && value)
	{
		free(var->value);
		free(key);
		var->value = value;
	}
	else if (!var)
	{
		var = var_new(key, value);
		if (!var)
			return (ERROR);
		var_add_back(var_list, var);
	}
	return (SUCCESS);
}

/*
Updates the alphabetic pointers of a var_list to include an added 
var.
*/
void	var_add_to_alpha(t_var *var, t_var *new)
{
	var = var->alpha;
	if (ft_strncmp(var->key, new->key, ft_strlen(var->key) + 1) > 0)
	{
		new->anext = var;
		while (var)
		{
			var->alpha = new;
			var = var->anext;
		}
		return ;
	}
	new->alpha = var;
	while (var->anext)
	{
		if (ft_strncmp(var->anext->key, new->key, ft_strlen(new->key) + 1) > 0)
		{
			new->anext = var->anext;
			var->anext = new;
			return ;
		}
		else
			var = var->anext;
	}
	var->anext = new;
}

/*
Removes the var corresponding to the given key from the var_list.
*/
void	var_remove_key(t_var **var_list, char *key)
{
	t_var	*var;
	t_var	*rmv;
	
	var = *var_list;
	if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
	{
		var_remove_from_alpha(*var_list, var);
		*var_list = var->next;
		var_delone(var);
	}
	while (var->next)
	{
		if (!ft_strncmp(var->next->key, key, ft_strlen(key) + 1))
		{
			rmv = var->next;
			var_remove_from_alpha(*var_list, rmv);
			var->next = rmv->next;
			var_delone(rmv);
		}
	}
}

/*
Removes the given var from the alphabetic pointer list.
*/
void	var_remove_from_alpha(t_var *var, t_var *rmv)
{
	var = var->alpha;
	if (var == rmv)
	{
		while (var)
		{
			var->alpha = rmv->anext;
			var = var->anext;
		}
	}
	else
	{
		while (var->anext != rmv)
			var = var->anext;
		var->anext = rmv->next;
	}
}
