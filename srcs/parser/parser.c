/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:14:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/03 10:05:03 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"

static void	parser_reset(t_parser *parser)
{
	parser->substring = NULL;
}

static void	parser_init(t_parser *parser)
{
	parser->substring = NULL;
	parser->token_list = NULL;
}

static int	parser_clean(t_parser *parser, int return_value)
{
	if (parser->substring)
		free(parser->substring);
	if (parser->token_list) 
		token_clear(&parser->token_list);
	return (return_value);
}

int	check_tokens(t_token *token, t_data *data)
{
	if (token->type == PIPE_TOKEN)
	{
		return (set_err(data, 2, "|"));
	}
	while (token)
	{
		token->cmd_num = data->cmd_count;
		if (token->type == PIPE_TOKEN)
			data->cmd_count++;
		if ((token->type == REDIR_TOKEN && !token->next) \
			|| (token->type == PIPE_TOKEN && !token->next))
				return (set_err(data, 2, \
				"newline"));
		else if ((token->type == REDIR_TOKEN \
			&& token->next->type != TEXT_TOKEN) || (token->type == PIPE_TOKEN \
			&& token->next->type == PIPE_TOKEN))
				return (set_err(data, 2, token->next->str));
		token = token->next;
	}
	return (SUCCESS);
}

int	parse(char *input, t_data *data)
{
	t_parser	parser;

	parser_init(&parser);
	if (check_quotes(input, data))
		return (ERROR);
	while (*input)
	{
		skip_whitespace(&input);
		if (!*input)
			break ;
		input = tokenize(input, &parser, data);
		if (!input)
			return (parser_clean(&parser, ERROR));
		parser_reset(&parser);
	}
	if (merge_tokens(&parser.token_list) \
		|| check_tokens(parser.token_list, data) \
		|| make_commands(&parser, data))
		return (parser_clean(&parser, ERROR));
	return (parser_clean(&parser, SUCCESS));
}
