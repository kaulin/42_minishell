/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:36:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/26 14:57:06 by jajuntti         ###   ########.fr       */
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

void	reset_data(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->error_msg)
		free(data->error_msg);
	if (data->cmd_list)
		cmd_clear(&data->cmd_list);
	data->o_stdin = dup(STDIN_FILENO);
	data->o_stdout = dup(STDOUT_FILENO);
	data->input = NULL;
	data->error_msg = NULL;
	data->cmd_list = NULL;
	data->cmd_count = 0;

}

void	clean_data(t_data *data)//need to add envp_clear
{
	if (data->input)
		free(data->input);
	if (data->cmd_list)
		cmd_clear(&data->cmd_list);
	if (data->error_msg)
		free(data->error_msg);
	if (data->envp)
		clean_array(data->envp);
	if (data->paths)
		clean_array(data->paths);
}

int	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->envp = copy_envp(data, envp);
	if (data->envp == NULL)
		return (ERROR);
	parse_paths(data);//where should this be? && error check?
	data->cmd_list = NULL;
	data->status = 0;
	data->error_msg = NULL;
	return (SUCCESS);
}
