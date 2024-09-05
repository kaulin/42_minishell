/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:26:14 by pik-kak           #+#    #+#             */
/*   Updated: 2024/09/05 14:03:17 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Looks for specific command in the paths of the environment variable.
*/
char	*find_cmd_path(t_data *data, char *cur_cmd)
{
	int		i;
	char	*cmd_path;

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
Adds the backslash symbol to all elements of a paths array.
*/
static int	complete_paths(char **paths)
{
	int		i;
	char	*joined_path;

	i = 0;
	while (paths[i])
	{
		joined_path = ft_strjoin(paths[i], "/");
		if (!joined_path)
			return (ERROR);
		free(paths[i]);
		paths[i] = joined_path;
		i++;
	}
	return (SUCCESS);
}

/*
Parses paths from environment variable and returns them as a null terminated 
array.
*/
char	**parse_paths(t_data *data)
{
	char	*path;
	char	**arr;

	path = var_get_value(data->envp_list, "PATH");
	if (!path)
	{
		arr = malloc(sizeof(char *));
		if (!arr)
			return (NULL);
		*arr = NULL;
		return (arr);
	}
	arr = ft_split(path, ":");
	if (!arr)
		return (ERROR);
	if (complete_paths(arr))
	{
		clean_array(arr);
		return (NULL);
	}
	return (arr);
}
