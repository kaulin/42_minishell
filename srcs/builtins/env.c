/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/04 13:34:35 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Env with no options or arguments
Env without any argument is used to print out a list
of all environment variables.
*/
//this needs to print only the variables that have values(=)
//we could transfer the argument count checks to the check builtin function?
//error message? Do we need to do something if envp is unset?
int	env_builtin(t_data *data, char **cmds)
{
	t_var	*var;

	if (cmds[1])
	{
		data->error_msg = ft_strdup("minishell: env: too many arguments");
		return (ERROR);
	}
	if (!data->envp_list)
	{
		data->error_msg = ft_strdup("Error, envp not set");
		return (ERROR);
	}
	var = data->envp_list;
	while (var)
	{
		if (var->value)
			printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (SUCCESS);
}
