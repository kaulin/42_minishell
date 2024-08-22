/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/22 13:27:40 by jajuntti         ###   ########.fr       */
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
		return (ERROR);
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
		if (parse(data.input, &data) || execute_and_pipe(&data))
		{
			if (!data.error_msg)
			{
				printf("Memory allocation error\n");
				clean_data(&data);
				return (EXIT_FAILURE);
			}
			printf("%s\n", data.error_msg);
			free(data.error_msg);
			data.error_msg = NULL;
		}
	}
	clean_data(&data);
	rl_clear_history();
	return 0;
}
