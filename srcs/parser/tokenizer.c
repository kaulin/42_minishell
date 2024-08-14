/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:35:10 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/14 13:44:16 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"

/*
Places the data from the tokens to the cmd struct TODO: error handling for 
adding input/output files.
*/
int	place_tokens(t_cmd *cmd, t_token **token_list)
{
	t_token	*this;
	
	this = *token_list;
	while (this)
	{
		if (is_redir_token(this))
		{
			if (!this->next || is_redir_token(this->next))
				return (ERROR);
			if (!ft_strncmp(this->str, "<", 2))
				file_add_back(&cmd->infiles, file_new(this->next->str, 0));
			else if (!ft_strncmp(this->str, "<<", 3))
				file_add_back(&cmd->infiles, file_new(this->next->str, 1));
			else if (!ft_strncmp(this->str, ">", 2))
				file_add_back(&cmd->outfiles, file_new(this->next->str, 0));
			else if (!ft_strncmp(this->str, ">>", 3))
				file_add_back(&cmd->outfiles, file_new(this->next->str, 1));
			this->placed_flag = 1;
			this->next->placed_flag = 1;
			this = this->next;
		}
		this = this->next;
	}
	cmd->cmd_str = merge_unused_tokens(*token_list);\
	if (!cmd->cmd_str)
		return (ERROR);
	return (SUCCESS);
}

char	*tokenize(char *input, t_parser *parser, t_data *data)
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
