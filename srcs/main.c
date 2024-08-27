/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/27 09:32:55 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Function gives the prompt and reads the users input to string. 
Readline allocates space for string automatically but doesn't free it.
*/

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;//Ignore arguments
	(void)argv;//Ignore arguments
	if (init_data(&data, envp))
	{
		printf("minishell: error setting up shell environment");
		return (ERROR);
	}
	signal(SIGINT, sigint_handler); //Handle Ctr+C
	signal(SIGQUIT, SIG_IGN); //Ignore Ctr+'\'
	while (1) 
	{
		reset_data(&data);
		data.input = readline("Minishell > ");
		if (data.input == NULL) //In case of Ctrl+D (EOF)
			break ;
		if (!*data.input)
			continue ;
		else
			add_history(data.input);
		if (parse(data.input, &data) | cmd_print(data.cmd_list) | execute_and_pipe(&data))
		{
			if (!data.error_msg)
				printf("Memory allocation error\n");
			else
				printf("%s\n", data.error_msg);
		}
	}
	clean_data(&data);
	rl_clear_history();
	printf("exit\n");
	return 0;
}
