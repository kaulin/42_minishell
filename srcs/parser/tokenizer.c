/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:35:10 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/18 09:53:47 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "expander.h"

/*
Moves the pointer ahead by one or two stops, depending on the command token. 
One step for |, < and >. Two steps for << and >>.
*/
static void	handle_special_char(char **ptr)
{
	if ((**ptr == '<' && *(*ptr + 1) == '<') \
		|| (**ptr == '>' && *(*ptr + 1) == '>'))
		(*ptr)++;
	(*ptr)++;
}

/*
Places unused text tokens belonging to the specific command into the command's 
cmd_arr. If the command has no unused text tokens, the command only 
contains redirects and a null pointer is placed in cmd_arr instead.
*/
static int	place_cmd_arr(t_cmd *cmd, t_token *token, int cmd_num, int i)
{
	int	unused_tokens;

	unused_tokens = token_count_unused(token, cmd_num);
	if (unused_tokens == 0)
	{
		cmd->cmd_arr = NULL;
		return (SUCCESS);
	}
	cmd->cmd_arr = ft_calloc((unused_tokens + 1), sizeof(char *));
	if (!cmd->cmd_arr)
		return (ERROR);
	while (i < unused_tokens)
	{
		if (token->cmd_num == cmd_num && token->type == TEXT_TOKEN \
			&& !token->placed_flag)
		{
			cmd->cmd_arr[i] = ft_strdup(token->str);
			if (!cmd->cmd_arr[i])
				return (ERROR);
			i++;
		}
		token = token->next;
	}
	cmd->cmd_arr[i] = NULL;
	return (SUCCESS);
}

/*
Places the data from the redir tokens to the cmd struct TODO: error handling for 
adding input/output files.
*/
static int	place_redirs(t_cmd *cmd, t_token *token, int cmd_num)
{
	t_redir	*file;

	file = NULL;
	while (token)
	{
		if (token->cmd_num == cmd_num && token->type == REDIR_TOKEN)
		{
			if (!ft_strncmp(token->str, "<", 2))
				file = redir_new(token->next->str, INFILE);
			else if (!ft_strncmp(token->str, "<<", 3))
				file = redir_new(token->next->str, HEREDOC);
			else if (!ft_strncmp(token->str, ">", 2))
				file = redir_new(token->next->str, OUTFILE);
			else
				file = redir_new(token->next->str, APPEND);
			if (!file)
				return (ERROR);
			redir_add_back(&cmd->redirects, file);
			token->next->placed_flag = 1;
			token = token->next;
		}
		token = token->next;
	}
	return (SUCCESS);
}

/*
Creates the correct number of commands into data->cmd_list and then places 
content from tokens into the commands in- and outfiles, as well as its command 
array.
*/
int	make_commands(t_parser *parser, t_data *data)
{
	int		cmd_num;
	t_cmd	*cmd_node;

	cmd_num = 1;
	while (cmd_num <= data->cmd_count)
	{
		cmd_node = cmd_new();
		if (!cmd_node)
			return (ERROR);
		if (place_redirs(cmd_node, parser->token_list, cmd_num) \
			|| place_cmd_arr(cmd_node, parser->token_list, cmd_num, 0))
		{
			cmd_delone(cmd_node);
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
			&& *input != '|' && *input != '<' && *input != '>')
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
