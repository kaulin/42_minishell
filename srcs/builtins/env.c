/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/22 14:21:20 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
◦ env with no options or arguments

Env without any argument is used to print out a list of all environment variables.
*/
void	free_copy(char **copy)
{
	int	i;

	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

int	arrange(char **copy, int i, int j)
{
	char	*temp;

	temp = strdup(copy[i]);
	if (temp == NULL)
		return (ERROR);
	copy[i] = strdup(copy[j]);
	if (copy[i] == NULL)
	{
		free(temp);
		return (ERROR);
	}
	copy[j] = strdup(temp);
	if (copy[j] == NULL)
	{
		free(temp);
		return (ERROR);
	}
	free(temp);
	return (SUCCESS);
}

int	env_in_order(t_data *data)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	copy = copy_envp(data, data->envp);
	if (!copy)
		return (ERROR);
	while (i < data->envp_count - 1)
	{
		j = i + 1;
		while (j < data->envp_count)
		{
			if (ft_strncmp(copy[i], copy[j], ft_strlen(copy[i]) + 1) > 0)
				if (arrange(copy, i, j) == 1)
				{
					free_copy(copy);
					return (ERROR);
				}
			j++;
		}
		printf("declare -x %s\n", copy[i]);
		i++;
	}
	free_copy(copy);
	return (SUCCESS);
}

int	env_builtin(t_data *data, char **cmds)//this needs to print only the variables that have values(=)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (cmds[1])//we could transfer the argument count checks to the check builtin function?
	{
		data->error_msg = ft_strdup("minishell: env: too many arguments");
		return (ERROR);
	}
	if (!data->envp)
	{
		data->error_msg = ft_strdup("Error, envp not set");//error message? Do we need to do something if envp is unset?
		return (ERROR);
	}
	while (data->envp[i] != NULL)
	{
		while (data->envp[i][len] != '=' && data->envp[i][len] != '\0')//would strcmp be better?
			len++;
		if ((data->envp[i])[len] == '=')
			printf("%s\n", data->envp[i]);
		i++;
		len = 0;
	}
	return (SUCCESS);
}
