/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/30 10:40:56 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
◦ env with no options or arguments

Env without any argument is used to print out a list of all environment variables.
*/

int	env_builtin(t_data *data, char **cmds)//this needs to print only the variables that have values(=)
{
	if (cmds[1])//we could transfer the argument count checks to the check builtin function?
	{
		data->error_msg = ft_strdup("minishell: env: too many arguments");
		return (ERROR);
	}
	if (!data->envp_list)
	{
		data->error_msg = ft_strdup("Error, envp not set");//error message? Do we need to do something if envp is unset?
		return (ERROR);
	}
	var_print_vars(data->envp_list, 0);
	return (SUCCESS);
}
