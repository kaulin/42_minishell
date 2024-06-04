/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:58:06 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/04 09:13:02 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

# include "parser.h"

typedef struct s_str
{
	char	*str;
	t_str	*next;
}	t_str;

typedef struct s_expander
{
	char	quote;
	char	*ptr;
	char	*key;
	char	*var;
	t_str	*str_list;
	t_str	*new_str;
}	t_expander;

// expander_utils.c
void	expander_init(t_expander *expander, char *str);
char	*trim_n(char **str, int n);

// splitjoin.c
int		splitjoin(char **str, char *delim, char *sep);

#endif
