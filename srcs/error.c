/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 08:24:58 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/05 14:19:40 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	oops(t_data *data, int e_code, char *e_file, char *e_str)
{
	if (e_code == QUOTE_E || e_code == TOKEN_E)
		e_code = 2;
	if (e_code == QUOTE_E)
		printf("mini: syntax error - unclosed quotations\n");
	else if (e_code == TOKEN_E)
		printf("mini: syntax error - unexpected token '%s'\n", e_str);
	else if (e_file && e_str)
		printf("mini: %s: %s\n", e_file, e_str);
	else if (!e_file && e_str)
		printf("mini: %s\n", e_str);
	else
		printf("mini: memory allocation error\n");
	data->status = e_code;
	data->error_handled = 1;
	return (e_code);
}
