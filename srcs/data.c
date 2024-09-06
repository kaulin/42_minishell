/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:36:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/06 14:26:01 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This copies the envp variables to a linked list and also stores it in a null 
terminated array.
*/
static int	copy_envp(t_data *data, char **envp)
{
	while (*envp)
	{
		if (var_add_var(&data->envp_list, *envp))
		{
			var_clear(&data->envp_list);
			return (ERROR);
		}
		envp++;
	}
	data->envp_arr = var_to_arr(data->envp_list);
	if (!data->envp_arr)
	{
		var_clear(&data->envp_list);
		return (ERROR);
	}
	return (SUCCESS);
}

int	update_envp(t_data *data)
{
	char	**temp;

	temp = var_to_arr(data->envp_list);
	if (!temp)
		return (ERROR);
	if (data->envp_arr)
		clean_array(data->envp_arr);
	data->envp_arr = temp;
	if (data->envp_arr)
	{
		temp = parse_paths(data);
		if (!temp)
			return (ERROR);
		if (data->paths)
			clean_array(data->paths);
		data->paths = temp;
	}
	return (SUCCESS);
}

void	reset_data(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->cmd_list)
		cmd_clear(&data->cmd_list);
	data->o_stdin = dup(STDIN_FILENO);
	data->o_stdout = dup(STDOUT_FILENO);
	data->input = NULL;
	data->cmd_list = NULL;
	data->cmd_count = 1;
	data->error_handled = 0;
	data->prev_status = data->status;
}

void	clean_data(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->cmd_list)
		cmd_clear(&data->cmd_list);
	if (data->envp_list)
		var_clear(&data->envp_list);
	if (data->envp_arr)
		clean_array(data->envp_arr);
	if (data->paths)
		clean_array(data->paths);
}

int	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->envp_arr = NULL;
	data->envp_list = NULL;
	if (copy_envp(data, envp))
		return (ERROR);
	data->paths = parse_paths(data);
	if (!data->paths)
	{
		var_clear(&data->envp_list);
		clean_array(data->envp_arr);
		return (ERROR);
	}
	data->o_stdin = dup(STDIN_FILENO);
	data->o_stdout = dup(STDOUT_FILENO);
	data->cmd_list = NULL;
	data->cmd_count = 1;
	data->error_handled = 0;
	data->status = 0;
	return (SUCCESS);
}
