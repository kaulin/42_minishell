/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:41:12 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/02 09:20:03 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns the number of nodes in a var_list.
*/
int	var_count(t_var *var)
{
	int	count;

	count = 0;
	while (var)
	{
		count++;
		var = var->next;
	}
	return (count);
}

/*
Looks for a var in the given list who's key matches the given key. Returns 
that var, or NULL if none found.
*/
t_var	*var_get_var(t_var *var, char *key)
{
	if (!key || !*key)
		return (NULL);
	while (var)
	{
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (var);
		var = var->next;
	}
	return (NULL);
}

/*
Looks for a var in the given list who's key matches the given key. Returns 
that vars value, or NULL if var is not found.
*/
char	*var_get_value(t_var *var, char *key)
{
	if (!key || !*key)
		return (NULL);
	while (var)
	{
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

/*
Converts the given var_list to a string array, which is returned.
*/
char	**var_to_arr(t_var *var_list)
{
	int		i;
	char	**var_arr;

	var_arr = malloc((var_count(var_list) + 1) * sizeof(char *));
	if (!var_arr)
		return (NULL);
	i = 0;
	while (var_list)
	{
		var_arr[i] = var_to_str(var_list);
		if (!var_arr[i])
		{
			clean_array(var_arr);
			return (NULL);
		}
		i++;
		var_list = var_list->next;
	}
	var_arr[i] = NULL;
	return (var_arr);
}
