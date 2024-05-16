/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/16 14:23:52 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ env with no options or arguments

Env without any argument is used to print out a list of all environment variables.
*/

int env_builtin(t_data *data)
{
    int i;

    i = 0;
    if (!data->envp)
        return (EXIT_FAILURE);//Should this give an error message?
    while (data->envp[i])
    {
        printf("%s\n", data->envp[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}