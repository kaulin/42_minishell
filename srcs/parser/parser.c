/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:14:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/30 15:20:35 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		while (*input && (!is_quote_char(*input) || !is_whitespace(*input)))
			input++;
	}
	parser->substring = ft_substr(parser->start, 0, input - parser->start - 1);
	if (!parser->substring)
		return (NULL);
	expand(parser->substring, data);
	if (!parser->substring)
		return (NULL);
	parser->new_token = token_new(parser->substring, *input);
	if (!parser->new_token)
		return (1);
	token_add_back(parser->token_list, parser->new_token);
	return (input);
}

int	parse(char *input, t_data *data)
{
	t_parser parser;

	if (check_quotes(input))
	{
		printf("Unclosed quotes!\n");
		return (1);
	}
	parser_init(&parser);
	while (*input)
	{
		if (is_whitespace(*input))
			input++;
		else
		{
			input = start_token(input, &parser, data);
			if (input = NULL)
				return (1);
			parser_reset(&parser);
		}
	}
	if (merge_tokens(parser.token_list))
		return (1); // clean return
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