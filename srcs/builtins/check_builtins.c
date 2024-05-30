/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:12:13 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/30 15:06:44 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


/*
This copies the envp variables and counts their amount
*/
char	**copy_envp(t_data *data, char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * i);
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = (char *)malloc(ft_strlen(envp[i]) + 1);
		copy[i] = envp[i];
		i++;
	}
	envp = copy;
	data->envp_count = i;
	return (copy);
}

void	init_data(t_data *data, char **envp)
{
	data->envp = copy_envp(data, envp);
	// if (data->envp == NULL)
	// 	error();
	data->cmd_list = NULL;
	data->status = 0;
	data->error_msg = NULL;
}

/*
This checks if the command is one of the builtins
*/
int check_if_builtin(t_data *data, char **cmds)
{
	(void)data;
	if (ft_strncmp("echo", cmds[0], 5) == 0)
		echo_builtin(cmds);
	// if (ft_strncmp("cd", cmds[0], 3) == 0)
	// 	cd_builtin(data, cmds);
	// if (ft_strncmp("env", cmds[0], 4) == 0)
	// 	env_builtin(data, cmds);
	// // if (ft_strncmp("exit", cmds[0], 5) == 0)
	// 	// 	exit_builtin();
	// if (ft_strncmp("export", cmds[0], 7) == 0)
	// 	export_builtin(data,cmds);
	if (ft_strncmp("pwd", cmds[0], 4) == 0)
		pwd_builtin(cmds);
	// if (ft_strncmp("unset", cmds[0], 6) == 0)
	// 	unset_builtin(data, cmds);
	return (0);
}
