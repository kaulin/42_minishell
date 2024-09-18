/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:24:02 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/18 12:41:32 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This prints the rest of the input
*/
void	print_cmd(char **cmds, int flag)
{
	if (flag == 0)
		cmds++;
	else if (flag == 1)
		cmds += 2;
	if (*cmds != NULL)
	{
		while (*cmds)
		{
			if (*(cmds + 1))
				printf("%s ", *cmds);
			else
				printf("%s", *cmds);
			cmds++;
		}
	}
	if (flag == 0)
		printf("\n");
}

/*
Checks if there is a -n flag (also -nn.. is acceptable)
*/
int	check_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	echo_builtin(char **cmd)
{
	int	flag;

	flag = 0;
	if (cmd && cmd[1])
		flag = check_flag(cmd[1]);
	print_cmd(cmd, flag);
	return (SUCCESS);
}
