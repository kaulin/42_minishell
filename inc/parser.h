/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:28:22 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/26 15:11:22 by jajuntti         ###   ########.fr       */
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

// parser_utils.c
int		is_quote_char(char c);
int		is_whitespace(char c);
void	skip_whitespace(char **ptr);
void	find_quote_end(char **ptr);
int		check_quotes(char *str, t_data *data);

// tokenizer.c
int		make_commands(t_parser *parser, t_data *data);
char	*tokenize(char *input, t_parser *parser, t_data *data);

// token_list.c
t_token	*token_new(char *content, char next);
void	token_add_back(t_token **token_list, t_token *new_token);
void	token_delone(t_token *token);
void	token_clear(t_token **token_list);
int		token_count_unused(t_token *token_list, int cmd_num);

// token_utils.c
int		is_redir_token(t_token *token);
int		is_pipe_token(t_token *token);
void	handle_special_char(char **input);
int		merge_tokens(t_token **token);
void	print_tokens(t_token *token_list);

#endif