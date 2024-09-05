/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:24:58 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/05 09:49:26 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	oops(t_data *data, int e_code, char *e_file, char *e_str)
{
	if (e_code == QUOTE_E || e_code == TOKEN_E)
		e_code = 2;
	if (e_code == QUOTE_E)
		printf("mini: syntax error, unclosed quotes\n", e_str);
	else if (e_code == TOKEN_E)
		printf("mini: syntax error near unexpected token '%s'\n", e_str);
	else if (e_file && e_str)
		printf("mini: %s: %s\n", e_file, e_str);
	else if (!e_file && e_str)
		printf("mini: %s", e_str);
	else
		printf("mini: memory error\n");
	data->status = e_code;
	return (e_code);
}
/*
void	syntax_err(t_data *data, char *err_str)
{
	char	*msg;

	msg = ft_strjoin ("mini: syntax error near unexpected token: ", err_str);
	data->error_msg = msg;
}

int	set_err(t_data *data, int err_code, char *err_str)
{
	data->status = err_code;
	if (err_code == SYNTAX_ERR)
		syntax_err(data, err_str);
	else
		data->error_msg = ft_strdup(err_str);
	return (ERROR);
}*/