/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/05 19:25:33 by kkauhane         ###   ########.fr       */
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
	char	*input;

	(void)argc;//Ignore arguments
	(void)argv;//Ignore arguments
	init_data(&data, envp);
	signal(SIGINT, sigint_handler); //Handle Ctr+C
	signal(SIGQUIT, SIG_IGN); //Ignore Ctr+'\'
	while (1) 
	{
		input = readline("Minishell > ");
		if (input == NULL) //In case of Ctrl+D (EOF)
			break ;
		if (input[0] != '\0')//do we need to also check for whitespaces only input?
			add_history(input);
		if (parse(input, &data))
		{
			printf("Memory allocation error\n");
			free(input);
			clean_data(&data);
			return (EXIT_FAILURE);
		}
		// execute commands from data->cmd_list, wait for possible children to complete and exit pipe with last command's exit code
	}
	clean_data(&data);
	return 0;
}
