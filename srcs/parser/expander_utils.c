/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:59:05 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/03 14:12:29 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expander_init(t_expander *expander, char *str)
{
	expander->quote = 0;
	if (is_quote_char(*str))
		expander->quote = *str;
	expander->ptr = str;
	expander->key = NULL;
	expander->var = NULL;
	expander->str_list = NULL;
	expander->new_str = NULL;
}

/*
Takes a pointer to a heap allocated string, makes a substring of it with int n 
characters trimmed from both ends, frees original string and replaces its 
pointer with the substring. If more characters would be trimmed than there are 
in the string, an empty string is used.
*/
int	trim_n(char **str, int n)
{
	char *temp;

	if (n * 2 >= ft_strlen(*str))
		temp = ft_strdup("");
	else
		temp = ft_substr(*str, n, ft_strlen(*str) - 2 * n);
	if (!temp)
		return (1);
	free(*str);
	*str = temp;
	return (0);
}