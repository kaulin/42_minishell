/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:12:34 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/22 14:24:01 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Displays the current working directory path.
 // PATH_MAX = Maximum number of bytes to store a pathname, including the terminating '\0'. From limits.h
*/

int	pwd_builtin(t_data *data, char **cmds)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	if (cmds[1])
	{
		data->error_msg = ft_strdup("minishell: pwd: invalid option");
		return (ERROR);
	}
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd)
	{
		printf("%s\n", cwd);
		return (SUCCESS);
	}
	return (ERROR);
}
