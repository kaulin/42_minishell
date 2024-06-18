/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:14:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/18 15:46:27 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"

static void	parser_reset(t_parser *parser)
{
	parser->substring = NULL;
	parser->start = NULL;
	parser->start = NULL;
}

static void	parser_init(t_parser *parser)
{
	parser->substring = NULL;
	parser->start = NULL;
	parser->start = NULL;
	parser->token_list = NULL;
}

static void	parser_clean(t_parser *parser)
{
	if (parser->substring)
		free(parser->substring);
	if (parser->token_list)
		token_clear(&parser->token_list);
}

static char	*tokenize(char *input, t_parser *parser, t_data *data)
{
	t_token	*node;
	
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
	if (expand(&parser->substring, data))
		return (NULL);
	node = token_new(parser->substring, *input);
	if (!node)
		return (NULL);
	token_add_back(&parser->token_list, node);
	return (input);
}

int	parse(char *input, t_data *data)
{
	t_parser parser;

	if (check_quotes(input))
	{
		data->error_msg = ft_strdup("Unclosed quotes!\n");
		return (ERROR);
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
				return (ERROR); // clean return
			parser_reset(&parser);
		}
	}
	print_tokens(&parser.token_list);
	if (merge_tokens(&parser.token_list))
		return (ERROR); // clean return
	print_tokens(&parser.token_list);
	parser_clean(&parser);
	return (SUCCESS);
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