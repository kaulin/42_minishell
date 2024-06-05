/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pik-kak <pik-kak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/05 17:00:19 by pik-kak          ###   ########.fr       */
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

int	env_in_order(t_data *data)
{
	int i;
	int j;
	char **copy;

	i = 0;
	copy = copy_envp(data, data->envp);
	if (!copy)
		return (EXIT_FAILURE);
	while (i < data->envp_count - 1)
	{
		j = i + 1;
		while (j < data->envp_count)
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
		ft_putendl_fd("Error", STDERR);//error message?
		return (EXIT_FAILURE);
	}
	while (data->envp[i] != NULL)
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
