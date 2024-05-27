/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:50:09 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/27 16:42:02 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
Export with no options
Is used to set environment variables(with or without values), making them available to child processes.
If a variable name is followed by =value, the value of the variable is set to value.
Shell variable names must start with a letter (a-z, A-Z) or an underscore (_).
They can contain letters, digits (0-9), or underscores.
They cannot contain special characters such as @, #, !, -, or spaces. 
Environmental variables normally contain only uppercase letters and '_'. Stick with that?
*/

int set_variable(t_data *data, char *cmd)
{
	char	**copy;
	int		i;

	i = 0;
	while (data->envp[i])
		i++;
	copy = (char **)malloc((i + 2) * sizeof(char *));
	if (!copy)
		return (EXIT_FAILURE);
	i = 0;
	while (data->envp[i])//copy the envp until the end and then add the new variable
	{
		copy[i] = data->envp[i];
		i++;
	}
	copy[i] = (char *)malloc(ft_strlen(cmd) + 1);//allocate the new variable
	if (!copy[i])
		return (EXIT_FAILURE);
	copy[i] = cmd;
	copy[++i] = NULL;
	data->envp = copy;
	return (EXIT_SUCCESS);
}

int check_key(t_data *data, char *cmd)//what if we give this one string
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (cmd[len] != '=' && cmd[len] != '\0')//get the length of the variable
		len++;
	while (data->envp[i])//go through the environmental variables
	{
		if (ft_strncmp(data->envp[i], cmd, len) == 0 && (data->envp[i])[len] == '=')
		{
			if (cmd[len] == '\0')//if there is no value we return
				return (EXIT_SUCCESS);
			data->envp[i] = cmd;//if there is a match and a value, we replace the old string with the new one. No need to free anything?
			return (EXIT_SUCCESS);
		}
		i++;
	}
	set_variable(data, cmd);//if we get to the end we need to allocate for a new variable and set it
	return (EXIT_SUCCESS);
}
int export_builtin(t_data *data, char **cmds)
{
	int		i;

	i = 1;
	if (!cmds[i])//If no names are supplied, a list of names of all variables is displayed in alphabetical order
		return (env_in_order(data));
	while (cmds[i])//go through the arguments and check each one and set them, in case of error return EXIT_FAILURE
	{
		check_key(data, cmds[i]);//these have been allocated already
		i++;
	}
	return (EXIT_SUCCESS);
}
