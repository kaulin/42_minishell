/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:22 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/16 14:05:39 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ unset with no options

unset [name]
Remove each variable or function name.
If no options are supplied, each name refers to a variable; if there is no variable by that name, a function with that name, if any, is unset(?).
Readonly variables and functions may not be unset. Some shell variables lose their special behavior if they are unset; such behavior is noted in the description of the individual variables. The return status is zero unless a name is readonly or may not be unset.
*/

void    unset_builtin(t_data *data)
{
    while (*data->env)//find the variable to unset and unset it if not found return error message?
    {

    }
}
