/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/29 14:40:24 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
◦ exit with no options

exit [n]
Exit the shell, returning the status of the last command executed to the shell’s parent.
Any trap on EXIT is executed before the shell terminates.
*/

// int	exit_builtin()
// {
		//free everything
		//return exitstatus
// }