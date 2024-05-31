/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:27:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/31 13:15:17 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
CLEANER FUNCTION NEEDED
*/

void	parser_reset(t_parser *parser)
{
	parser->substring = NULL;
	parser->start = NULL;
	parser->start = NULL;
}

void	parser_init(t_parser *parser)
{
	parser->substring = NULL;
	parser->start = NULL;
	parser->start = NULL;
	parser->token_list = NULL;
	parser->new_token = NULL;
}

int	is_quote_char(char c)
{
	if (ft_strchr ("\'\"", c))
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if (ft_strchr (" \t\v\n\r\f", c))
		return (1);
	return (0);
}

void	skip_whitespace(char **ptr)
{
	while (is_whitespace(**ptr))
		(*ptr)++;
}
