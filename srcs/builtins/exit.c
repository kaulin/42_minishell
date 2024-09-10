/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/10 09:24:10 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
Exit with no options
Exit the shell, returning the status of the last command executed
to the shell’s parent.
Any trap on EXIT is executed before the shell terminates.
exit must print "exit"
Should this be void?
*/

void	exit_builtin(t_data *data)
{
	clean_data(data);
	printf("exit\n");
	exit(data->prev_status);
}
