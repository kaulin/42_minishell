/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:14:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/31 13:24:47 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
Checks whether the given string contains unclosed single or double quotes. 
Returns 1 if there are unclosed quotes.
*/
static int	check_quotes(char *str)
{
	char	*quote;

	quote = NULL;
	while (*str)
	{s
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

char	*tokenize(char *input, t_parser *parser, t_data *data)
{
	parser->start = input;
	if (is_quote_char(*input))
	{
		parser->quote = input++;
		while (*input != *parser->quote)
			input++;
		input++;
	}
	else
	{
		while (*input && !is_quote_char(*input) && !is_whitespace(*input))
			input++;
	}
	parser->substring = ft_substr(parser->start, 0, input - parser->start);
	if (!parser->substring)
		return (NULL);
	expand(&parser->substring, 0, data);
	if (!parser->substring)
		return (NULL);
	parser->new_token = token_new(parser->substring, *input);
	if (!parser->new_token)
		return (NULL);
	token_add_back(&parser->token_list, parser->new_token);
	return (input);
}

int	parse(char *input, t_data *data)
{
	t_parser parser;

	if (check_quotes(input))
	{
		printf("Unclosed quotes!\n");
		return (1); // clean return
	}
	parser_init(&parser);
	while (*input)
	{
		if (is_whitespace(*input))
			input++;
		else
		{
			input = tokenize(input, &parser, data);
			if (!input)
				return (1); // clean return
			parser_reset(&parser);
		}
	}
	print_tokens(&parser.token_list);
	if (merge_tokens(&parser.token_list))
		return (1); // clean return
	print_tokens(&parser.token_list);
	return (0);
}
	/*
	After tokenization:
	- define token types
	- separate into commands based on |
	- assing into command structs and their variables
	*/

/*
Cases
"$ec""$ho"
"$ec""$space""$ho"
"$ec""$null""$ho"
*/