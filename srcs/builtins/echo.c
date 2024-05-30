/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:24:02 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/30 14:35:54 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
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
	if (*cmds != '\0')
	{
		while(*cmds)
		{
			printf("%s", *cmds);
			cmds++;
		}
	}
	if (flag == 0)
		printf("\n");
}

int	check_flag(char *arg)//this checks if there is a -n flag (also -nn.. is acceptable)
{
	int i;

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

int	echo_builtin(char **cmd)//Argument form must be desided. Example here is command cmd[0], flag cmd[1], and the printable part cmd[2]
{
	int flag;

	flag = 0;
	if (cmd && cmd[1])
		flag = check_flag(cmd[1]);//if there is a valid -n-flag we print with \n else without
	print_cmd(cmd, flag);
	return (EXIT_SUCCESS);
}