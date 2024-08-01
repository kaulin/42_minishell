/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/01 15:27:10 by jajuntti         ###   ########.fr       */
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
	while (is_whitespace(**ptr))
		(*ptr)++;
}

void	find_quote_end(char **ptr)
{
	char	quote;

	quote = **ptr;
	(*ptr)++;
	while (**ptr != quote)
		(*ptr)++;
	(*ptr)++;
}

/*
Checks whether the given string contains unclosed single or double quotes. 
Returns 1 if there are unclosed quotes.
*/
int	check_quotes(char *str)
{
	char	*quote;

	quote = NULL;
	while (*str)
	{
		if (!quote)
		{
			if (is_quote_char(*str))
				quote = str;
		}
		else
			if (*str == *quote)
				quote = NULL;
		str++;
	}
	if (quote)
		return (*quote);
	return (0);
}