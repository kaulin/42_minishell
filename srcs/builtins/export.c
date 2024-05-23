/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:50:09 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/23 15:52:00 by kkauhane         ###   ########.fr       */
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

// int set_variable(t_data *data, char *key, char *value)
// {
// 	char **copy;
// 	size_t  len;
// 	int i;

// 	i = 0;
// 	len = ft_strlen(key);
// 	copy = data->envp;
// 	while (*data->envp)//copy the envp until the end and then add the new variable
// 	{
// 		*copy = *data->envp;
// 		i++;
// 	}
// 	*copy[i] = (char *)malloc(len + ft_strlen())//we need to allocate enought
// 	return (EXIT_SUCCESS);
// }

int check_key(t_data *data, char *key, char *value)
{
	int	len;
	char *var_copy;
	int i;

	len = ft_strlen(key);
	i = 0;
	while (data->envp[i])//go through the environmental variables
	{
		if (ft_strncmp(data->envp[i], key, len) == 0 && (data->envp[i])[len] == '=')
		{
			if (value == NULL)
				return (EXIT_SUCCESS);
			else //if there is a match and a value, we reallocate and replace the value with the new value
			{
				//free(*data->envp);//free the old key_value_pair;
				var_copy = ft_strjoin(key, value);//this allocates for var_copy and frees key
				//free(value);
				data->envp[i] = var_copy;
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	//set_variable(data, key, value);//if we get to the end we need to allocate for a new variable and set it
	return (EXIT_SUCCESS);
}
int export_builtin(t_data *data, char **cmds)
{
	int i;
	char *key;
	char *value;
	char *pointer;

	i = 1;
	value = NULL;
	key = NULL;
	if (!cmds[i])//If no names are supplied, a list of names of all variables is displayed
	{
		env_builtin(data);
		return (EXIT_SUCCESS);
	}
	while (cmds[i])//go through the arguments and check each one and set them, in case of error return EXIT_FAILURE
	{
		pointer = ft_strchr(cmds[i], '=');
		if (pointer == NULL)//if there isn't a '=' copy the name of the variable to key
			key = ft_strdup(cmds[i]);
		else
		{
			value = ft_strdup(pointer);
			key = (char *)malloc(ft_strlen(cmds[i]) - ft_strlen(value) + 1);
			ft_strlcpy(key, cmds[i], (ft_strlen(cmds[i]) - ft_strlen(value) + 1));
		}
		check_key(data, key, value);//these have been allocated already
		i++;
	}
	return (EXIT_SUCCESS);
}
