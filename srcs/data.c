/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:36:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/05 19:00:22 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This copies the envp variables and counts their amount
*/

char	**copy_envp(t_data *data, char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (i > 0)
                free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	data->envp_count = i;
	return (copy);
}

void	clean_data(t_data *data)//need to add envp_clear
{
	if (data->cmd_list)
		cmd_clear(&data->cmd_list);
	if (data->error_msg)
		free(data->error_msg);
	rl_clear_history();
}

void	init_data(t_data *data, char **envp)
{
	data->envp = copy_envp(data, envp);
	//if (data->envp == NULL)//if copy failed
		//error();
	data->cmd_list = NULL;
	data->status = 0;
	data->error_msg = NULL;
}
