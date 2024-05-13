/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/13 12:56:59 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Function gives the prompt and reads the users input to string. 
Readline allocates space for string automatically but doesn't free it.
*/

int main(int argc, char **argv, char **envp)
{
    char *input;

    (void)argc;//Ignore arguments
    (void)argv;
	(void)envp;
	signal(SIGINT, sigint_handler); //Handle Ctr+C
	signal(SIGQUIT, SIG_IGN); //Ignore Ctr+'\'
    while (1) 
    {
        input = readline("Minishell > ");
        if (input == NULL) //In case of Ctrl+D (EOF)
            break;
        // if (input[0] != '\0')
        //     add_history(input);
        free(input);
    }
    return 0;
}
