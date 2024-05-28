/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:40:26 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/27 14:51:57 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


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

int	merge_tokens(t_token *token)
{
	while (token)
	{
		if (merge_token(token))
			return (1);
		token = token->next;
	}
	return (0);
}

void	define_tokens(t_token *token)
{
	token->type = 0;
}