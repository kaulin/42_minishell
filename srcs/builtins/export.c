/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:50:09 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/30 14:37:00 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Export with no options
Is used to set environment variables(with or without values), making them available to child processes.
If a variable name is followed by =value, the value of the variable is set to value.
Shell variable names must start with a letter (a-z, A-Z) or an underscore (_).
They can contain letters, digits (0-9), or underscores.
They cannot contain special characters such as @, #, !, -, or spaces. 
Environmental variables normally contain only uppercase letters and '_'. Stick with that?
*/

int	export_builtin(t_data *data, char **cmds)
{
	int		i;

	i = 1;
	if (!cmds[i])
		var_print_vars(data->envp_list, 1);
	while (cmds[i])
	{
		if (var_add_var(&data->envp_list, cmds[i]))
			return (ERROR);
		i++;
	}
	if (update_envp(data))
		return (ERROR);
	return (SUCCESS);
}
