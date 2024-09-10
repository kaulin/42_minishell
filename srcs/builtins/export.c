/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:50:09 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/10 09:08:43 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Export with no options
Is used to set environment variables(with or without values),
making them available to child processes.
If a variable name is followed by =value,
the value of the variable is set to value.
Shell variable names must start with a letter (a-z, A-Z) or an underscore (_).
They can contain letters, digits (0-9), or underscores.
They cannot contain special characters such as @, #, !, -, or spaces. 
Environmental variables normally contain only uppercase letters and '_'.
Stick with that?
*/

static int	check_name(char *cmd)
{
	while (*cmd)
	{
		if (ft_isalpha(*cmd) == 1 || ft_isdigit(*cmd) == 1 || *cmd != '_')
			return (ERROR);
		cmd++;
	}
	return (SUCCESS);
}

static void	print_variables(t_var *var)
{
	while (var)
	{
		if (var->value)
			printf("declare -x %s=\"%s\"\n", var->key, var->value);
		else
			printf("declare -x %s\n", var->key);
		var = var->anext;
	}
}

int	export_builtin(t_data *data, char **cmds)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmds[i])
		print_variables(data->envp_list->alpha);
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '=') == cmds[i] || check_name(cmds[i]) == 1)
		{
			oops(data, 1, "export: not a valid identifier", cmds[i]);
			flag = 1;
		}
		else if (var_add_var(&data->envp_list, cmds[i]) || update_envp(data))
			return (ERROR);
		i++;
	}
	return (flag);
}
