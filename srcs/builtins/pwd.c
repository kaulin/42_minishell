/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:12:34 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/07 18:55:53 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Displays the current working directory path.
 // PATH_MAX = Maximum number of bytes to store a pathname, including the terminating '\0'. From limits.h
*/

int	pwd_builtin(char **cmds)
{
	char	*cwd;
	char	buffer[PATH_MAX];

	if (cmds[1])
	{
		ft_putstr_fd("minishell: pwd: ", STDERR);
		ft_putstr_fd(cmds[1], STDERR);
		ft_putendl_fd(": invalid option", STDERR);
		return (EXIT_FAILURE);
	}
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd)
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
