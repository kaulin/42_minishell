
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pik-kak <pik-kak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:26:14 by pik-kak           #+#    #+#             */
/*   Updated: 2024/06/06 11:33:40 by pik-kak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Looks for specific command in the paths of the environment variable.
*/
char	*find_cmd_path(t_data *data, char *cur_cmd)
{
	int		i;
	char 	*cmd_path;

	i = 0;
	if (!data->paths)
		return (NULL);
	while (data->paths[i])
	{
		cmd_path = ft_strjoin(data->paths[i], cur_cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0 && is_directory(cmd_path) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

/*
Parses paths from environment variable.
*/
void	parse_paths(t_data *data)
{
	int		i;
	char	*joined_path;

	i = 0;
	if (!data->envp_arr)
		return ;
	while (data->envp_arr[i] && ft_strncmp(data->envp_arr[i], "PATH=", 5))
		i++;
	if (!data->envp_arr[i] || !data->envp_arr[i][5])
		return ;
	data->paths = ft_split(&data->envp_arr[i][5], ":");
	if (!*data->paths)
		return ;
	i = 0;
	while (data->paths[i])
	{
		joined_path = ft_strjoin(data->paths[i], "/");
		if (!joined_path)
		{
			clean_array(data->paths);
			return ;
		}
		free(data->paths[i]);
		data->paths[i++] = joined_path;
	}
}
