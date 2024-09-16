/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/16 15:05:08 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

static void	setup_signal_handling(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, basic_handler);
}


static void	check_signal(t_data *data)
{
	if (g_signal)
		data->prev_status = 130;
	g_signal = 0;
}

static void	handle_input(t_data *data)
{
	add_history(data->input);
	if (parse(data->input, data) && !data->error_handled)
		oops(data, 1, NULL, NULL);
	if (data->cmd_list && execute_and_pipe(data) == ERROR && !data->error_handled)
		oops(data, 1, NULL, NULL);
}

/*
Function gives the prompt and reads the users input to string. 
Readline allocates space for string automatically but doesn't free it.
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data || init_data(data, envp))
		return (oops(data, 1, NULL, "error setting up shell environment"));
	setup_signal_handling();
	while (42)
	{
		data->status = 0;
		data->input = readline("mini -> ");
		check_signal(data);
		if (data->input == NULL)
			break ;
		if (*data->input)
			handle_input(data);
		reset_data(data);
		setup_signal_handling();
	}
	rl_clear_history();
	printf("exit\n");
	exit(clean_data(data));
	return (ERROR);
}
