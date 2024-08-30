/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:14:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/08/30 13:10:11 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// Todo: Handle ${} expansion
// Todo: Handle $1 $2 etc, ie Positional parameters?
// Todo: Handle $(cmd) execution, ie Command substitution?

/*
Clears the malloced str_list nodes in the expander struct.
*/
static void	expander_clean(t_expander *expander)
{
	if (expander->str_list)
		str_clear(&expander->str_list);
}

/*
Initializes the expander struct. Sets expander->quote character to the 
first character of the string, if that character is ' or "", and expander->ptr 
to the start of the parameter str.
*/
static void	expander_init(t_expander *expander, char *str)
{
	expander->quote = 0;
	if (is_quote_char(*str))
		expander->quote = *str;
	expander->ptr = str;
	expander->var = NULL;
	expander->str_list = NULL;
}

/*
Expands the environment variables in the given string. Returns the expanded 
string, or ERROR if errors occur.
*/
int	expand(char **str, t_data *data)
{
	t_expander	expander;

	expander_init(&expander, *str);
	if (expander.quote && trim_n(&expander.ptr, 1))
	{
		expander_clean(&expander);
		return (ERROR);
	}
	while (*expander.ptr)
	{
		if (cut_str(&expander))
			return (ERROR);
	}
	if (expander.quote != '\'' && expand_strings(&expander, data))
	{
		expander_clean(&expander);
		return (ERROR);
	}
	free(*str);
	*str = str_merge(expander.str_list);
	expander_clean(&expander);
	if (!*str)
		return (ERROR);
	return (SUCCESS);
}
