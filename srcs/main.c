/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:36 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/10 15:54:54 by kkauhane         ###   ########.fr       */
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
    while (1) 
    {
        signal(SIGINT, sigint_handler); //Handle Ctr+C
        signal(SIGQUIT, SIG_IGN); //Ignore Ctr+\
        input = readline("Minishell > ");
        if (input == NULL) //In case of Ctrl+D (EOF)
            break;
        // if (input[0] != '\0')
        //     add_history(input);
        free(input);
    }
    return 0;
}
