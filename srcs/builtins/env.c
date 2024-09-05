/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/05 13:16:54 by jajuntti         ###   ########.fr       */
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
		return (oops(data, 1, "env", "too many arguments"));
	if (!data->envp_list)
		return (oops(data, 1, "env", "envp not set"));
	var = data->envp_list;
	while (var)
	{
		if (var->value)
			printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (SUCCESS);
}
