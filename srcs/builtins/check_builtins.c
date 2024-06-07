/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:12:13 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/07 18:46:57 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This checks if the command is one of the builtins
*/
int	check_if_builtin(t_data *data, char **cmds)
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
	return (0);
}
