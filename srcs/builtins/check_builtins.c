/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:12:13 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/01 13:38:54 by pikkak           ###   ########.fr       */
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
		return (1);
	return (0);
}

/*
Executes the builtin in question
Commands that produce output can be redirected so we we need to check redirections before executing commands.
*/
int	execute_builtin(t_data *data, char **cmds)
{
	(void)data;
	if (ft_strncmp("echo", cmds[0], 5) == 0)
		echo_builtin(cmds);
	if (ft_strncmp("cd", cmds[0], 3) == 0)
		cd_builtin(data, cmds);
	if (ft_strncmp("env", cmds[0], 4) == 0)
		env_builtin(data, cmds);
	// if (ft_strncmp("exit", cmds[0], 5) == 0)
		// 	exit_builtin();
	if (ft_strncmp("export", cmds[0], 7) == 0)
		export_builtin(data, cmds);
	if (ft_strncmp("pwd", cmds[0], 4) == 0)
		pwd_builtin(cmds);
	if (ft_strncmp("unset", cmds[0], 6) == 0)
		unset_builtin(data, cmds);
	else
		return (1);
	return (0);
}
