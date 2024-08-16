/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:14:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/16 12:05:17 by jajuntti         ###   ########.fr       */
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
	parser->start = NULL;
	parser->substring = NULL;
	parser->token_list = NULL;
}

static void	parser_clean(t_parser *parser)
{
	if (parser->substring)
		free(parser->substring);
	if (parser->token_list)
		token_clear(&parser->token_list);
}

/*
Splits the given commands cmd_str into tokens, which are expanded and merged 
where necessary.
*/
int	parse_cmd(t_cmd *cmd, t_data *data)
{
	t_parser	parser;
	char		*input;

	input = cmd->cmd_str;
	parser_init(&parser);
	printf("Tokenizing cmd: %s\n", input); // REMOVE
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
	printf("Expanding tokens\n"); // REMOVE
	print_tokens(parser.token_list);
	printf("Expanding tokens\n"); // REMOVE
	if (merge_tokens(&parser.token_list) \
		|| place_tokens(cmd, parser.token_list) \
		|| place_tokens(cmd, parser.token_list))
	{
		parser_clean(&parser);
		return (ERROR);
	}
	print_tokens(parser.token_list);
	parser_clean(&parser);
	return (SUCCESS);
}

/*
Makes a new cmd_str from the given start and end pointers, places that into 
a new cmd_node and adds that node to the back of the cmd_list.
*/
int	split_command(char *start, char *end, t_data *data)
{
	char	*cmd_str;
	t_cmd	*cmd_node;

	cmd_str = ft_substr(start, 0, end - start);
	if (!cmd_str)
		return (ERROR);
	cmd_node = cmd_new(cmd_str);
	if (!cmd_node)
	{
		free(cmd_str);
		return (ERROR);
	}
	cmd_add_back(&data->cmd_list, cmd_node);
	return (SUCCESS);
}

/*
Checks the input for unclosed quotes and erroneous pipe characters. Then 
splits the input into separate commands based on unquoted pipe characters. 
Finally parses each of these commands.
*/
int	parse(char *input, t_data *data)
{
	t_cmd	*cmd;
	char	*start;
	
	if (check_quotes(input, data)) // || check_pipes(input, data);
		return (ERROR);
	start = input;
	while (*input)
	{
		if (is_quote_char(*input))
			find_quote_end(&input);
		if (*input == '|')
		{
			if (split_command(start, input - 1, data))
				return (ERROR);
			start = ++input;
			continue ;
		}
		input++;
	}
	if (start != input)
	{
		if (split_command(start, input, data))
			return (ERROR);
	}
	cmd = data->cmd_list;
	while (cmd)
	{
		if (parse_cmd(cmd, data))
			return (ERROR);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/*
After tokenization:
- define token types
- assing into command structs and their variables
*/
