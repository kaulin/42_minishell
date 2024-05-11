/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>            +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:43:22 by kkauhane           #+#    #+#            */
/*   Updated: 2024/05/11 13:35:38 by kkauhane          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
• In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
*/

void    sigint_handler(int signal)
{
	(void)signal;
    struct termios handler; //This is used for handling terminal I/O (input/output) settings. Can be found from termios.h

    if (tcgetattr(0, &handler) == -1) //This function gets the terminal attributes(initializes the handler)
    {
        perror("Error in retrieving the terminal attributes");
    }
    if (tcsetattr(0, 0, &handler) == -1) //Sets the attributes of the terminal associated with file descriptor 0 (standard input) using the values stored in handler
    {
        perror("Error in setting the terminal attributes");
    }
	write(1, "\n", 1); //Prints newline
	rl_on_new_line(); // Moves readline to the newline
	rl_replace_line("", 0); //Replaces the previous readline with the new one
	rl_redisplay(); //Redisplays the prompt
}
