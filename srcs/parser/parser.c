/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:14:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/05 13:10:43 by jajuntti         ###   ########.fr       */
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

int	parse_cmd(t_cmd *cmd, t_data *data)
{
	t_parser	parser;
	char		*input;

	input = cmd->cmd_str;
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

int	parse(char *input, t_data *data)
{
	t_cmd		*cmd;
	t_parser	parser;

	if (check_quotes(input))
	{
		data->error_msg = ft_strdup("minishell: syntax error: unclosed quotations\n");
		return (ERROR);
	}
	parser_init(&parser);
	while (*input)
	{
		skip_whitespace(&input);
		if (*input = '|')
		{
			data->error_msg = ft_strdup("minishell: syntax error near unexpected token \`|'");
			input++;
			continue ;
		}
		while (*input)
		{
			parser.start = input;
			if (is_quote_char(*input))
				find_quote_end(&input);
			
		}
		
	}

}
	/*
	After tokenization:
	- define token types
	- separate into commands based on |
	- assing into command structs and their variables

	If | without command before it
	** bash: syntax error near unexpected token `|'
	If ||
	** bash: syntax error near unexpected token `||'


	*/

/*
Cases
"$ec""$ho"
"$ec""$space""$ho"
"$ec""$null""$ho"
*/