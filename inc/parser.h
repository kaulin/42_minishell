/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:28:22 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/12 12:58:38 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// Types of tokens
# define REDIR_TKN 1;
# define CMD_TKN 2;
# define OPT_TKN 3;
# define ARG_TKN 4;
# define PIPE_TKN 5;

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
	int				type;
	struct s_token	*next;
	int				merge_flag;
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
int		check_quotes(char *str);

// token_list.c
t_token	*token_new(char *content, char next);
void	token_add_back(t_token **token_list, t_token *new_token);
void	token_delone(t_token *token);
void	token_clear(t_token **token_list);

// token_utils.c
int		merge_tokens(t_token **token);
void	define_tokens(t_token *token);
void	print_tokens(t_token **token_list);

#endif