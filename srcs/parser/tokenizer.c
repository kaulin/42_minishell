/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:35:10 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/27 09:22:20 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"

static int	place_cmd_array(t_cmd *cmd, t_token *token_list, int cmd_num)
{
	int	unused_tokens;
	int	i;

	unused_tokens = token_count_unused(token_list, cmd_num);
	i = 0;
	cmd->cmd_arr = ft_calloc((unused_tokens + 1), sizeof(char*));
	if (!cmd->cmd_arr)
		return (ERROR);
	while (token_list && i < unused_tokens)
	{
		if (!token_list->placed_flag)
		{
			cmd->cmd_arr[i] = ft_strdup(token_list->str);
			if (!cmd->cmd_arr[i])
				return (ERROR);
			i++;
		}
		token_list = token_list->next;
	}
	cmd->cmd_arr[i] = NULL;
	return (SUCCESS);
}

/*
Places the data from the redir tokens to the cmd struct TODO: error handling for 
adding input/output files.
*/
static int	place_tokens(t_cmd *cmd, t_token *token_list, int cmd_num)
{
	t_token	*this;
	
	this = token_list;
	while (this)
	{
		if (this->cmd_num == cmd_num && this->type == REDIR_TOKEN)
		{
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
	return (place_cmd_array(cmd, token_list, cmd_num));
}

/*

*/
int	make_commands(t_parser *parser, t_data *data)
{
	int		cmd_num;
	t_cmd	*cmd_node;

	cmd_num = 1;
	while (cmd_num <= data->cmd_count)
	{
		cmd_node = cmd_new();
		if (!cmd_node || place_tokens(cmd_node, parser->token_list, cmd_num))
			return (ERROR);
		if (place_tokens(cmd_node, parser->token_list, cmd_num))
		{
			free(cmd_node);
			return (ERROR);
		}
		cmd_add_back(&data->cmd_list, cmd_node);
		cmd_num++;
	}
	return (SUCCESS);
}

char	*tokenize(char *input, t_parser *parser, t_data *data)
{
	t_token	*node;
	
	parser->start = input;
	if (is_quote_char(*input))
	{
		find_quote_end(&input);
		input++;
	}
	else if (*input == '|' || *input == '<' || *input == '>')
		handle_special_char(&input);
	else
	{
		while (*input && !is_quote_char(*input) && !is_whitespace(*input) \
			&& (*input != '|' || *input != '<' || *input != '>'))
			input++;
	}
	parser->substring = ft_substr(parser->start, 0, input - parser->start);
	if (!parser->substring || expand(&parser->substring, data))
		return (NULL);
	node = token_new(parser->substring, *input);
	if (!node)
		return (NULL);
	token_add_back(&parser->token_list, node);
	return (input);
}
