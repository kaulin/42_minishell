/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/26 20:29:13 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
◦ exit with no options

exit [n]
Exit the shell, returning the status of the last command executed to the shell’s parent.
Any trap on EXIT is executed before the shell terminates.
Should this be void?
*/

int	exit_builtin(t_data *data)//do we need to have an exit_code variable in data to preserve the last exit code??
{
	fail(0, "Exit\n", data);
	return ();
}