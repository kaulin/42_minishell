/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:12:34 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/11 12:25:38 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	(void)cmds;
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd)
		printf("%s\n", cwd);
	else if (var_get_var(data->envp_list, "PWD"))
		printf("%s\n", var_get_value(data->envp_list, "PWD"));
	//else if (data->cwd && *data->cwd)
	//	printf("%s\n", data->cwd);
	else
		return (oops(data, 1, NULL, "pwd failed"));
	return (SUCCESS);
}
