/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/18 12:45:20 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Removes the variable
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
