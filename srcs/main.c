/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/12 09:57:10 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_in_heredoc;

/*
Set up signal handlers for SIGINT and SIGUSR1.
Calls the correct handlers.
*/
void	setup_signal_handling(t_data *data, void (*handler)(int))
{
	struct sigaction	sa;
	struct sigaction	sa_usr;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		oops(data, 1, NULL, "sigaction for SIGINT failed");
	sa_usr.sa_handler = sigusr1_handler;
	sigemptyset(&sa_usr.sa_mask);
	sa_usr.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa_usr, NULL) == -1)
		oops(data, 1, NULL, "sigaction for SIGUSR1 failed");
}

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
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data || init_data(data, envp))
		return (oops(data, 1, NULL, "error setting up shell environment"));
	g_in_heredoc = 0;
	while (42)
	{
		setup_signal_handling(data, basic_signal_handler);
		data->status = 0;
		data->input = readline("mini -> ");
		if (data->input == NULL)
			break ;
		if (*data->input)
			handle_input(data);
		reset_data(data);
	}
	rl_clear_history();
	printf("exit\n");
	exit(clean_data(data));
	return (ERROR);
}
