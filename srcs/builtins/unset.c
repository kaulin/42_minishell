/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/30 15:10:29 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ unset with no options

Unset name...
Remove each variable or function name. 
EXIT STATUS        
    0    All name operands were successfully unset.

    >0    At least one name could not be unset.
Each name refers to a variable; if there is no variable by that name, a function with that name, if any, is unset(?).
Readonly variables and functions may not be unset. Do we need to check?
The memory for envp is managed by the operating system, and reallocation/deallocation is not required.
*/

int unset(t_data *data, char *variable)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(variable);
	while (data->envp[i])
	{
		// if (ft_strncmp(data->envp[i], variable, len) == 0 && data->envp[i][len] == '=')// || data->envp[i][len] == '\0'))//this finds the variable, what if there is no value
		// {
		// 	//free(data->envp[i]);
		// 	//data->envp[i] =  NULL;
			
		// 	printf("%s\n", data->envp[++i]);
		// 	//*data->envp = ++(*data->envp);
		// }
		printf("%s\n", data->envp[i]);
		i++;//we go forward until we find the variable
	}
	return (EXIT_SUCCESS);
}

// int unset(t_data *data, char *variable)
// {
// 	size_t	len;
// 	char	**pointer;
// 	int	i;

// 	i = 0;
// 	len = ft_strlen(variable);
// 	pointer = data->envp;
// 	while (*data->envp)
// 	{
// 		if (ft_strncmp(*data->envp, variable, len) == 0 && (*data->envp)[len] == '=')
// 			data->envp++;
// 		pointer[i] = *data->envp;
// 		i++;
// 		data->envp++;
// 	}
// 	pointer[i] = NULL;
// 	data->envp = pointer;
// 	return (EXIT_SUCCESS);
// }

int unset_builtin(t_data *data, char **cmds)
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
		while (data->envp[i] && ft_strncmp(*cmds, data->envp[i], ft_strlen(*cmds) != 0))
			i++;
		if (!data->envp[i])
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
