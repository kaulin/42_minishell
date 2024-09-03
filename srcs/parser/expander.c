/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:14:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/03 12:01:05 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
static int	expander_init(t_expander *expander, char **str)
{
	char	*temp;

	expander->quote = 0;
	if (is_quote_char(**str))
	{
		expander->quote = **str;
		temp = ft_substr(*str, 1, ft_strlen(*str) - 2);
		if (!temp)
			return (ERROR);
		free(*str);
		*str = temp;
	}
	expander->ptr = *str;
	expander->var = NULL;
	expander->str_list = NULL;
	return (SUCCESS);
}

/*
Expands the environment variables in the given string. Returns the expanded 
string, or ERROR if errors occur.
*/
int	expand(char **str, t_data *data)
{
	t_expander	expander;

	if (expander_init(&expander, str))
		return (ERROR);
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
