/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/16 14:23:52 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ env with no options or arguments

Env without any argument is used to print out a list of all environment variables.
*/
void	free_copy(char **copy)
{
	int i;

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
	char *temp;

	temp = strdup(copy[i]);
	if (temp == NULL)
		return (EXIT_FAILURE);
	copy[i] = strdup(copy[j]);
	if (copy[i] == NULL)
	{
		free(temp);
		return (EXIT_FAILURE);
	}
	copy[j] = strdup(temp);
	if (copy[j] == NULL)
	{
		free(temp);
		return (EXIT_FAILURE);
	}
	free(temp);
	return (EXIT_SUCCESS);
}

char	**copy_env(t_data *data, int len)
{
	int i;
	char **copy;

	i = 0;
	copy = (char **)malloc((len + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (data->envp[i])
	{
		copy[i] = (char *)malloc((ft_strlen(data->envp[i]) + 1) * sizeof(char));
		if (!copy[i])
			return (NULL);
		copy[i] = data->envp[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	env_in_order(t_data *data)
{
	int i;
	int j;
	int len;
	char **copy;

	i = 0;len = 0;
	while (data->envp[len])
		len++;
	copy = copy_env(data, len);
	if (!copy)
		return (EXIT_FAILURE);
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(copy[i], copy[j], ft_strlen(copy[i]) + 1) > 0)
				if (arrange(copy, i, j) == 1)
				{
					free_copy(copy);
					return (EXIT_FAILURE);
				}
			j++;
		}
		printf("declare -x %s\n", copy[i]);
		i++;
	}
	free_copy(copy);
	return (EXIT_SUCCESS);
}

int env_builtin(t_data *data, char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("minishell: env: too many arguments", STDERR);
		return (EXIT_FAILURE);
	}
	if (!data->envp)
	{
		ft_putendl_fd("Error", STDERR);
		return (EXIT_FAILURE);
	}
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
