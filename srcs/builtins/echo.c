/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:24:02 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/04 13:32:24 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
◦ Echo with option -n
    - Used to print text/variables to the terminal(syntax: echo 'sample text')
	- If there is no text to print echo prints a new line
    - With -n do not output a trailing newline.
	-Can this command fail somehow?
	-Problem with two words with a ' ' in the middle and no ""
*/

void	print_cmd(char **cmds, int flag)//this prints the rest of the input
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
