/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:50:09 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/18 12:43:33 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Sets environment variables(with or without values).
If a variable name is followed by =value,
the value of the variable is set to value.
*/
static int	check_name(char *cmd)
{
	if (ft_isdigit(*cmd) || (!ft_isalpha(*cmd) && *cmd != '_'))
		return (ERROR);
	while (*cmd && *cmd != '=')
	{
		if (!ft_isalnum(*cmd) && *cmd != '_')
			return (ERROR);
		cmd++;
	}
	return (SUCCESS);
}

static void	print_variables(t_var *var)
{
	while (var)
	{
		if (var->value)
			printf("declare -x %s=\"%s\"\n", var->key, var->value);
		else
			printf("declare -x %s\n", var->key);
		var = var->anext;
	}
}

int	export_builtin(t_data *data, char **cmds)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmds[i])
		print_variables(data->envp_list->alpha);
	while (cmds[i])
	{
		if (check_name(cmds[i]))
		{
			oops(data, 1, "export: not a valid identifier", cmds[i]);
			flag = 1;
		}
		else if (var_add_var(&data->envp_list, cmds[i]) || update_envp(data))
			return (ERROR);
		i++;
	}
	return (flag);
}
