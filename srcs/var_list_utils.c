/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:41:12 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/30 15:16:04 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*var_get_value(t_var *var, char *key)
{
	while (var)
	{
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

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

char	**var_to_arr(t_var *var_list)
{
	int		var_index;
	t_var	*var;
	char	**var_arr;

	var_index = 0;
	var = var_list;
	while (var)
	{
		var_index++;
		var = var->next;
	}
	var_arr = malloc((var_index + 1) * sizeof(char *));
	if (!var_arr)
		return (NULL);
	var_index = 0;
	while (var_list)
	{
		var_arr[var_index] = var_to_str(var_list);
		if (!var_arr[var_index])
		{
			clean_array(var_arr);
			return (NULL);
		}
		var_index++;
		var_list = var_list->next;
	}
	var_arr[var_index] = NULL;
	return (var_arr);
}
