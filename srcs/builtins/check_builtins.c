/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:12:13 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/19 11:39:12 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This checks if the command is one of the builtins
*/
int	check_if_builtin(char **cmds)
{
	if (!cmds)
		return (0);
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
	if (ft_strncmp("exit", cmds[0], 5) == 0 && data->cmd_count == 1)
		exit_builtin(data);
	return (SUCCESS);
}
