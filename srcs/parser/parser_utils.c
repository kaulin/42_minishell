/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/29 14:51:37 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

/*
CLEANER FUNCTION NEEDED
*/

void	init_parser(t_parser *parser)
{
	parser->substring = NULL;
	parser->quote_start = NULL;
	parser->string_start = NULL;
	parser->token_list = NULL;
	parser->new_token = NULL;
}

int	is_quote_char(char c)
{
	if (ft_strchr ("\'\"", c))
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if (ft_strchr (" \t\v\n\r\f", c))
		return (1);
	return (0);
}

void	skip_whitespace(char **ptr)
{
	while (is_whitespace(**ptr))
		(*ptr)++;
}

/*
Expands the environment variables in the given string. Returns the expanded 
string, or NULL if errors occur.
*/
char	*expand_variables(char **str, t_data *data)
{
	(void)str;
	(void)data;
/*
	char	*original;
	char	*tail;
	char	*variable;
	int		index;

	original = *str;
*/
	return (NULL);
}