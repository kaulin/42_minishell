/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_getters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:41:12 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/30 09:48:02 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_get_var(t_var *var, char *key)
{
	while (var)
	{
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (var);
		var = var->next;
	}
	return (NULL);
}

void	print_vars(t_var *var_list, int order_flag)
{
	t_var	*var;

	var = var_list;
	if (order_flag)
		var = var->alpha;
	while (var)
	{
		if (order_flag)
		{
			printf("declare -x %s=\"%s\"\n", var->key, var->value);
			var = var->anext;
		}
		else
		{
			printf("%s=%s\n", var->key, var->value);
			var = var->next;
		}
	}
}

char	**var_to_arr(t_var *var_list)
{
	int		var_index;
	char	**var_arr;

	var_index = 0;
	while (var_list + var_index)
		var_index++;
	var_arr = malloc((var_index + 1) * sizeof(char *));
	if (!var_arr)
		return (NULL);
	var_index = 0;
	while (var_list + var_index)
	{
		var_arr[var_index] = var_to_str(var_list);
		if (!var_arr[var_index])
		{
			clean_array(var_arr);
			return (NULL);
		}
		var_index++;
	}
	var_arr[var_index] = NULL;
	return (var_arr);
}
