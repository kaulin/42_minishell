/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/10 16:56:08 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//volatile sig_atomic_t my_signal;
//void setup_signal_handling();
volatile sig_atomic_t in_heredoc;

static void	handle_input(t_data *data)
{
	add_history(data->input);
	if (parse(data->input, data) && !data->error_handled)
		oops(data, 1, NULL, NULL);
	if (data->cmd_list && execute_and_pipe(data) && !data->error_handled)
		oops(data, 1, NULL, NULL);
}

/*
Function gives the prompt and reads the users input to string. 
Readline allocates space for string automatically but doesn't free it.
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;//Ignore arguments
	(void)argv;//Ignore arguments
	if (init_data(&data, envp))
		return (oops(&data, 1, NULL, "error setting up shell environment"));
	in_heredoc = 0;
	setup_signal_handling(NULL);
	while (42)
	{
		data.status = 0;
		data.input = readline("mini -> ");
		if (data.input == NULL) //In case of Ctrl+D (EOF)
			break ;
		if (*data.input)
			handle_input(&data);
		reset_data(&data);
	}
	clean_data(&data);
	rl_clear_history();
	printf("exit\n");
	exit(data.prev_status);
	return (ERROR);
}
