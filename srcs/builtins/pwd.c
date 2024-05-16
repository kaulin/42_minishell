/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:12:34 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/16 14:17:36 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ pwd with no options
Displays the current working directory path.
*/

int pwd_builtin(t_data *data)
{
    char *cwd;
    char buffer[PATH_MAX]; // PATH_MAX = Maximum number of bytes to store a pathname, including the terminating '\0'. From limits.h

    cwd = getcwd(buffer, PATH_MAX);
    if (cwd)
    {
        printf("%s\n", cwd);
        return (EXIT_SUCCESS);
    }
    else
        return (EXIT_FAILURE);
    //should we free the cwd?
}