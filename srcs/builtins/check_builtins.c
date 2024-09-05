/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:12:13 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/05 11:54:57 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This checks if the command is one of the builtins
*/

int	check_if_builtin(char **cmds)
{
	if (ft_strncmp("echo", cmds[0], 5) == 0
		|| ft_strncmp("cd", cmds[0], 3) == 0
		|| ft_strncmp("env", cmds[0], 4) == 0
		|| ft_strncmp("exit", cmds[0], 5) == 0
		|| ft_strncmp("export", cmds[0], 7) == 0
		|| ft_strncmp("pwd", cmds[0], 4) == 0
		|| ft_strncmp("unset", cmds[0], 6) == 0)
		return (ERROR);
	return (SUCCESS);
}

/*
Executes the builtin in question
Commands that produce output can be redirected
so we we need to check redirections before executing commands.
How do we handle builtins failing?
*/
int	exec_builtin(t_data *data, char **cmds)
{
	if (!cmds)
		return (SUCCESS);
	if (ft_strncmp("echo", cmds[0], 5) == 0)
		return (echo_builtin(cmds));
	if (ft_strncmp("cd", cmds[0], 3) == 0)
		return (cd_builtin(data, cmds));
	if (ft_strncmp("env", cmds[0], 4) == 0)
		return (env_builtin(data, cmds));
	if (ft_strncmp("export", cmds[0], 7) == 0)
		return (export_builtin(data, cmds));
	if (ft_strncmp("pwd", cmds[0], 4) == 0)
		return (pwd_builtin(data, cmds));
	if (ft_strncmp("unset", cmds[0], 6) == 0)
		return (unset_builtin(data, cmds));
	if (ft_strncmp("exit", cmds[0], 5) == 0)
		exit_builtin(data);
	return (SUCCESS);
}
