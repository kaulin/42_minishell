/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:40:26 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/14 13:41:17 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir_token(t_token *token)
{
	if (!ft_strncmp(token->str, "<", 2) || !ft_strncmp(token->str, "<<", 3) \
		|| !ft_strncmp(token->str, ">", 2) || !ft_strncmp(token->str, ">>", 3))
		return (1);
	return (0);
}

char	*merge_unused_tokens(t_token *token)
{
	char	*temp_str;
	char	*return_str;

	temp_str = NULL;
	return_str = NULL;
	while(token)
	{
		if (!token->placed_flag)
		{
			temp_str = ft_strjoin(return_str, " ");
			if (!temp_str && return_str)
			{
				free(return_str);
				return (NULL);
			}
			if (return_str)
				free(return_str);
			return_str = ft_strjoin(temp_str, token->str);
			free(temp_str);
			if (!return_str)
				return (NULL);
		}
		token = token->next;
	}
	return (return_str);
}

/*
If the token given as an argument is mergeable, merge it with the next token. 
Their contents are concatenated and the token receives the mergeable and next 
values from the second token. The second token is freed. Loops until token is 
not mergeable any more.
*/
static int	merge_token(t_token *token)
{
	t_token	*temp_ptr;
	char	*temp_str;

	while (token->merge_flag)
	{
		temp_ptr = token->next;
		temp_str = ft_strjoin(token->str, token->next->str);
		if (!temp_str)
			return (1);
		free(token->str);
		token->str = temp_str;
		token->merge_flag = token->next->merge_flag;
		token->next = token->next->next;
		token_delone(temp_ptr);
	}
	return (0);
}

int	merge_tokens(t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		if (merge_token(token))
			return (1);
		token = (token)->next;
	}
	return (0);
}

void	print_tokens(t_token **token_list)
{
	int		count;
	t_token	*token;

	count = 0;
	token = *token_list;
	while (token)
	{
		printf("Token %d contains: %s\n", count, token->str);
		count++;
		token = token->next;
	}
}