/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:12:34 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/11 15:35:29 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"\

/*
Displays the current working directory path.
PATH_MAX = Maximum number of bytes to store a pathname,
including the terminating '\0'. From limits.h
*/
int	pwd_builtin(t_data *data, char **cmds)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	if (cmds[1])
		return (oops(data, 2, "pwd", "invalid option"));
	cwd = getcwd(buffer, PATH_MAX);
	if (!cwd && var_get_value(data->envp_list, "PWD"))
		cwd = var_get_value(data->envp_list, "PWD");
	else if (data->cwd && *data->cwd)
		cwd = data->cwd;
	else
		return (oops(data, 1, NULL, "getpwd failed"));
	printf("%s\n", cwd);
	return (SUCCESS);
}
