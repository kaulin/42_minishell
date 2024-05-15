/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:38 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/13 14:32:41 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ env with no options or arguments

Env without any argument is used to print out a list of all environment variables.
*/

int env_builtin(t_data *data)
{
    if (!data->envp)
        return (EXIT_FAILURE);//Should this give an error message?
    while (*data->envp)
    {
        printf("%s\n", *data->envp);
        data->envp++;
    }
    return (EXIT_SUCCESS);
}