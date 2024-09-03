/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:24:58 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/03 10:05:42 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err(t_data *data, int err_code, char *err_str)
{
	char	*msg;

	data->status = err_code;
	msg = ft_strjoin ("mini: syntax error near unexpected token: ", err_str);
	data->error_msg = msg;
}

int	set_err(t_data *data, int err_code, char *err_str)
{
	if (err_code == SYNTAX_ERR)
		syntax_err(data, err_code, err_str);
	else
		data->error_msg = ft_strdup(err_str);
	return (ERROR);
}