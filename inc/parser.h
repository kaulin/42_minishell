/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:28:22 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/16 10:59:51 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*
Defines linked list token struct.
@str		Token content in string form
@type		Integer value representing type of token
@next		Pointer to next token in list
@merge_flag	Integer value, 1 if token is mergeable with next, 0 if not.
*/
typedef struct s_token
{
	char			*str;
	struct s_token	*next;
	int				merge_flag;
	int				placed_flag;
}	t_token;

typedef struct s_parser
{
	char			*substring;
	char			*quote;
	char			*start;
	t_token			*token_list;
}	t_parser;

// parser_utils.c
int		is_quote_char(char c);
int		is_whitespace(char c);
void	skip_whitespace(char **ptr);
void	find_quote_end(char **ptr);
int		check_quotes(char *str, t_data *data);

// tokenizer.c
int		place_tokens(t_cmd *cmd, t_token *token_list);
char	*tokenize(char *input, t_parser *parser, t_data *data);

// token_list.c
t_token	*token_new(char *content, char next);
void	token_add_back(t_token **token_list, t_token *new_token);
void	token_delone(t_token *token);
void	token_clear(t_token **token_list);

// token_utils.c
int		is_redir_token(t_token *token);
char	*merge_unused_tokens(t_token *token);
int		merge_tokens(t_token **token);
void	define_tokens(t_token *token);
void	print_tokens(t_token **token_list);

#endif