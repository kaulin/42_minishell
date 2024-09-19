/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:29:36 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/19 12:27:22 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
Creates a new token struct and initialises its str with the parameter sting. 
A pointer to the new_token is returned, unless there is a malloc 
*/
t_token	*token_new(char *content, int quote_flag, char next)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = content;
	new_token->next = NULL;
	new_token->merge_flag = 0;
	if (is_pipe_token(new_token))
		new_token->type = PIPE_TOKEN;
	else if (is_redir_token(new_token))
		new_token->type = REDIR_TOKEN;
	else
	{
		new_token->type = TEXT_TOKEN;
		if (next && !is_whitespace(next) \
		&& next != '|' && next != '<' && next != '>')
			new_token->merge_flag = 1;
	}
	printf("%s - %d - %c\n", content, quote_flag, next);
	if (!ft_strncmp(content, "$", 2) && next \
		&& !quote_flag && is_quote_char(next))
		*content = 0;
	new_token->placed_flag = 0;
	return (new_token);
}

/*
Adds the new_token to the end of the token_list. If token_list is empty to 
start with, token_list is set equal to the new_token.
*/
void	token_add_back(t_token **token_list, t_token *new_token)
{
	t_token	*temp;

	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		temp = *token_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
	}
}

/*
Frees the contents of the given token struct and then frees the struct pointer.
*/
void	token_delone(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->str)
		free(token->str);
	free(token);
}

/*
Frees all the tokens and their contents in a token_list.
*/
void	token_clear(t_token **token_list)
{
	t_token	*next;

	if (token_list == NULL)
		return ;
	while (*token_list)
	{
		next = (*token_list)->next;
		token_delone(*token_list);
		*token_list = next;
	}
}

/*
Counts the number of unused text tokens for a specific command, so that 
the command array can be allocated properly.
*/
int	token_count_unused(t_token *token_list, int cmd_num)
{
	int	i;

	i = 0;
	while (token_list)
	{
		if (token_list->cmd_num == cmd_num \
			&& token_list->type == TEXT_TOKEN \
			&& !token_list->placed_flag)
			i++;
		token_list = token_list->next;
	}
	return (i);
}
