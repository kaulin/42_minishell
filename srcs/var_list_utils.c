/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:41:12 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/02 09:12:19 by jajuntti         ###   ########.fr       */
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
Prints the variables in the var_list. If in_order_flag is set, values are 
printed in the style of the export command. Otherwise basic env printout is 
followed and vars without a set value are omitted.
*/
void	var_print_vars(t_var *var_list, int in_order_flag)
{
	t_var	*var;

	if (in_order_flag)
	{
		var = var_list->alpha;
		while (var)
		{
			if (var->value)
				printf("declare -x %s=\"%s\"\n", var->key, var->value);
			else
				printf("declare -x %s\n", var->key);
			var = var->anext;
		}
	}
	else
	{
		var = var_list;
		while (var)
		{
			if (var->value)
				printf("%s=%s\n", var->key, var->value);
			var = var->next;
		}
	}
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
