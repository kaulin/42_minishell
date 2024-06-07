/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/07 18:57:35 by kkauhane         ###   ########.fr       */
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
Each name refers to a variable; if there is no variable by that name, a function with that name, if any, is unset(?).
Readonly variables and functions may not be unset. Do we need to check?
*/

int	unset(t_data *data, char *variable)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(variable);
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], variable, len) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = NULL;
			data->envp[i] = ++(*data->envp);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	unset_builtin(t_data *data, char **cmds)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	cmds++;
	if (!*cmds)
		return (EXIT_SUCCESS);
	while (*cmds != '\0')
	{
		while (data->envp[i] && ft_strncmp(*cmds, data->envp[i], \
				ft_strlen(*cmds) != 0))
			i++;
		if (data->envp[i] == NULL)
			flag = 1;
		else
			unset(data, *cmds);
		i = 0;
		cmds++;
	}
	if (flag != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
