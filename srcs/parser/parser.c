/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:14:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/28 15:29:59 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse(char *input, t_data *data)
{
	t_parser parser;

	init_parser(&parser);
	while (*input)
	{
		skip_whitespace(&input);
		if (!parser.quote_start && is_quote_char(*input))
			parser.quote_start = input;
		else if (parser.quote_start && *input == *parser.quote_start)
		{
			parser.substring = ft_substr(parser.quote_start, 1, input - parser.quote_start);
			parser.quote_start = NULL;
			if (!parser.substring)
				return (1); // clean return
			if (parser.quote_start == '\"')
				expand_variables(&parser.substring, data);
			parser.new_token = tokenize(parser.substring, *(input + 1));
			token_add_back(parser.token_list, parser.new_token);


		}
	}
	if (merge_tokens(parser.token_list))
		return (1); // clean return
	return (0);
}

/*
Cases
"$ec""$ho"
"$ec""$space""$ho"
"$ec""$null""$ho"
*/