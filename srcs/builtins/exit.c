/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/04 13:37:31 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Exit with no options
Exit the shell, returning the status of the last command executed
to the shell’s parent.
Any trap on EXIT is executed before the shell terminates.
Should this be void?
*/

void	exit_builtin(t_data *data)
{
	fail(0, "exit\n", data);
}
