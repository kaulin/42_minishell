/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/07 16:18:34 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
◦ unset with no options

Unset name...
Remove each variable or function name. 
EXIT STATUS        
    0    All name operands were successfully unset.
    >0    At least one name could not be unset.
Each name refers to a variable; if there is no variable by that name,
a function with that name, if any, is unset(?).
Readonly variables and functions may not be unset. Do we need to check?
*/

int	unset_builtin(t_data *data, char **cmds)
{
	t_var	*var;

	cmds++;
	if (!*cmds)
		return (SUCCESS);
	while (*cmds)
	{
		var = var_get_var(data->envp_list, *cmds);
		if (var)
		{
			var_remove_key(&data->envp_list, *cmds);
			if (update_envp(data))
				return (ERROR);
		}
		cmds++;
	}
	return (SUCCESS);
}
