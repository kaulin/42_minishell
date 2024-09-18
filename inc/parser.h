/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:28:22 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/18 16:22:03 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define TEXT_TOKEN 0
# define REDIR_TOKEN 1
# define PIPE_TOKEN 2

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
	int				cmd_num;
	int				type;

}	t_token;

typedef struct s_parser
{
	char			*substring;
	char			*start;
	t_token			*token_list;
}	t_parser;

// parser.c
int		parse(char *input, t_data *data);

// parser_utils.c
void	skip_whitespace(char **ptr);
void	find_quote_end(char **ptr);
int		check_quotes(char *str);

// tokenizer.c
int		make_commands(t_parser *parser, t_data *data);
char	*tokenize(char *input, t_parser *parser, t_data *data);

// token_list.c
t_token	*token_new(char *content, int quote_flag, char next);
void	token_add_back(t_token **token_list, t_token *new_token);
void	token_delone(t_token *token);
void	token_clear(t_token **token_list);
int		token_count_unused(t_token *token_list, int cmd_num);

// token_utils.c
int		is_redir_token(t_token *token);
int		is_pipe_token(t_token *token);
int		merge_tokens(t_token **token);

#endif