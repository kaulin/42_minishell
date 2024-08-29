/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:58:06 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/29 10:34:28 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

# include "parser.h"

typedef struct s_str
{
	char			*str;
	struct s_str	*next;
}	t_str;

typedef struct s_expander
{
	char			quote;
	char			*ptr;
	char			*start;
	char			*var;
	t_str			*str_list;
}	t_expander;

// expander.c
int		expand(char **str, t_data *data);

// expander_utils.c
char	*get_var(char *key, t_data *data);
int		trim_n(char **str, unsigned int n);

// splitjoin.c
int		splitjoin(char **str, char *delim, char *sep);

// str_list.c
t_str	*str_new(char *content);
void	str_add_back(t_str **str_list, t_str *new_str);
void	str_delone(t_str *str);
void	str_clear(t_str **str_list);
char	*str_merge(t_str *str_list);

#endif
