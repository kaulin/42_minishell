/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/18 12:42:10 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Prints out a list of all environment variables.
*/
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
