/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:09 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/13 14:26:49 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
Export with no options
Is used to set environment variables(with or without values), making them available to child processes.
If a variable name is followed by =value, the value of the variable is set to value.
Shell variable names must start with a letter (a-z, A-Z) or an underscore (_).
They can contain letters, digits (0-9), or underscores.
They cannot contain special characters such as @, #, !, -, or spaces. 
Environmental variables normally contain only uppercase letters and '_'. Stick with that?
*/

int set_variable(t_data *data, char **key_value)
{

}

int check_key(t_data *data, char *key)
{

}

char    **check_value(char *arg)
{
    char *pointer;
    char **key_value;

    pointer = ft_strchr(arg, '=');//check for '=' if there is one split it into two and return it?
   // if (pointer == 0)
    return(key_value);
}

int export_builtin(t_data *data, char **cmds)
{
    int i;
    char **key_value;

    i = 1;
    if (!cmds[i])
        env_builtin(data);//If no names are supplied, a list of names of all variables is displayed
    while (cmds[i])//go through the arguments and check each one and set them, in case of error return EXIT_FAILURE
    {
        key_value = check_value(cmds[i]);//check if there is a '=' and separate the name from the possible value
        check_key(key_value[1]);//check if there is a variable of that name and set the value given.If there isn't check if the name given is valid
        set_variable();// and then set the variable and it's value
        i++;
    }
}
