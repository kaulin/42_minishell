/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/16 14:40:16 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ unset with no options

Unset name...
Remove each variable or function name. 
EXIT STATUS        
    0    All name operands were successfully unset.

    >0    At least one name could not be unset.
Each name refers to a variable; if there is no variable by that name, a function with that name, if any, is unset(?).
Readonly variables and functions may not be unset.
The memory for envp is managed by the operating system, and reallocation/deallocation is not required.
*/

int error_message(char **cmds, char *message)//this is temporary
{
    printf("%s: %s\n", *cmds, message);
    exit (1);
}

int unset(t_data *data, char *variable)
{
    size_t  len;
    char    **pointer;
    int     i;

    i = 0;
    len = ft_strlen(variable);
    pointer = data->envp;
    while (*data->envp)
    {
        if (ft_strncmp(*data->envp, variable, len) == 0 && (*data->envp)[len] == '=')
        {
            data->envp++;
            continue ;
        }
        pointer[i] = *data->envp;
        i++;
        data->envp++;
    }
    pointer[i] = NULL;
    data->envp = pointer;
    return (EXIT_SUCCESS);
}

int unset_builtin(t_data *data, char **cmds)
{
    int i;
    int flag;

    i = 0;
    flag = 0;//this flags unsuccessfull unsets
    cmds++;
    if (!*cmds)
        error_message(--cmds, "not enough arguments");
    while (*cmds != '\0')
    {
        while (data->envp[i] && ft_strncmp(*cmds, data->envp[i], ft_strlen(*cmds) != 0))//find the variable to unset and unset it if not found return error message?
            i++;
        if (!data->envp[i])
            flag = 1;
        else
            unset(data, *cmds);
        i = 0;
        cmds++;
    }
    if (flag != 0)
    {
        error_message(--cmds, "could not unset variable\n");//to be removed
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
