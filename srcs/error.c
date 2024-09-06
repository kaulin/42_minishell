/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:24:58 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/06 11:37:15 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(char *e_str)
{
	if (!e_str)
		ft_putstr_fd("mini: syntax error - unclosed quotations\n", 2);
	else
	{
		ft_putstr_fd("mini: syntax error - unexpected token '", 2);
		ft_putstr_fd(e_str, 2);
		ft_putendl_fd("'", 2);
	}
	return (2);
}

static int	cmd_not_found_error(char *e_file, char *e_str)
{
	if (e_file && !ft_strncmp(e_file, ".", 2))
	{
		ft_putendl_fd(\
		".: filename argument required\n.: usage: . filename [arguments]", 2);
		return (2);
	}
	if (e_str)
	{
		ft_putstr_fd("mini: ", 2);
		ft_putstr_fd(e_file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(e_str, 2);
	}
	else
	{
	ft_putstr_fd(e_file, 2);
	ft_putendl_fd(": command not found", 2);
	}
	return (127);
}

int	oops(t_data *data, int e_code, char *e_file, char *e_str)
{
	if (e_code == SYNTAX_E)
		e_code = syntax_error(e_str);
	else if (e_code == NO_CMD_E)
		e_code = cmd_not_found_error(e_file, e_str);
	else if (e_file && e_str)
	{
		ft_putstr_fd("mini: ", 2);
		ft_putstr_fd(e_file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(e_str, 2);
	}
	else if (!e_file && e_str)
	{
		ft_putstr_fd("mini: ", 2);
		ft_putendl_fd(e_str, 2);
	}
	else
		ft_putendl_fd("mini: memory allocation error", 2);
	data->status = e_code;
	data->error_handled = 1;
	return (e_code);
}
 