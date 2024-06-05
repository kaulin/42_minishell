/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:36:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/05 12:01:46 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_data(t_data *data)
{
	if (data->cmd_list)
		cmd_clear(&data->cmd_list);
	if (data->error_msg)
		free(data->error_msg);
}

void	init_data(t_data *data, char **envp)
{
	data->envp = copy_envp(data, envp);
	data->cmd_list = NULL;
	data->status = 0;
	data->error_msg = NULL;
}
