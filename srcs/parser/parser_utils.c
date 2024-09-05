/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/05 10:10:43 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_quote_char(char c)
{
	if (ft_strchr("\'\"", c))
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if (ft_strchr(" \t\v\n\r\f", c))
		return (1);
	return (0);
}

void	skip_whitespace(char **ptr)
{
	while (**ptr && is_whitespace(**ptr))
		(*ptr)++;
}

void	find_quote_end(char **ptr)
{
	char	quote;

	quote = **ptr;
	(*ptr)++;
	while (**ptr && **ptr != quote)
		(*ptr)++;
}

/*
Checks whether the given string contains unclosed single or double quotes. 
Sets error message and returns ERROR if there are unclosed quotes.
*/
int	check_quotes(char *str, t_data *data)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (!quote && is_quote_char(*str))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		str++;
	}
	if (quote)
		return (ERROR);
	return (SUCCESS);
}
