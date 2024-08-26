/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:50:09 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/26 20:15:09 by pikkak           ###   ########.fr       */
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

int	set_variable(t_data *data, char *cmd)
{
	char	**copy;
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	copy = (char **)malloc((i + 2) * sizeof(char *));
	if (!copy)
		return (ERROR);//should this be a fail?
	i = 0;
	while (data->envp[i])
	{
		copy[i] = data->envp[i];
		i++;
	}
	copy[i] = (char *)malloc(ft_strlen(cmd) + 1);
	if (!copy[i])
		return (free(copy), ERROR);
	copy[i] = ft_strdup(cmd);
	copy[++i] = NULL;
	free(data->envp);
	data->envp = copy;
	return (SUCCESS);
}

int	check_key(t_data *data, char *cmd)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (cmd[len] != '=' && cmd[len] != '\0')
		len++;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], cmd, len) == 0 && (data->envp[i])[len] == '=')
		{
			if (cmd[len] == '\0')
				return (SUCCESS);
			free(data->envp[i]);
			data->envp[i] = ft_strdup(cmd);
			return (SUCCESS);
		}
		i++;
	}
	set_variable(data, cmd);
	return (SUCCESS);
}

int	export_builtin(t_data *data, char **cmds)
{
	int		i;

	i = 1;
	if (!cmds[i])
		return (env_in_order(data));
	while (cmds[i])
	{
		check_key(data, cmds[i]);
		i++;
	}
	return (SUCCESS);
}
