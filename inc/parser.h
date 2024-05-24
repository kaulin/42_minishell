/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:28:22 by jajuntti          #+#    #+#             */
/*   Updated: 2024/05/24 10:43:46 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define REDIR_TKN = 1;
# define CMD_TKN = 2;
# define OPT_TKN = 3;
# define ARG_TKN = 4;
# define PIPE_TKN = 5;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

// token_list.c
t_token	*token_new(char *content);
void	token_add_back(t_token **token_list, t_token *new_token);
void	token_delone(t_token *token);
void	token_clear(t_token **token_list);

// token_utils.c4
void	define_token(t_token *token);

#endif