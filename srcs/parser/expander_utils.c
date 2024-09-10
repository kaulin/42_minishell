/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:59:05 by jajuntti          #+#    #+#             */
/*   Updated: 2024/09/10 12:21:31 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
Traverses the given string. If the first character is alphabetic or 
an underscore, continues as long as the characters are alphanumeric or 
underscores. If the first character is numeric, only jumps one character 
ahead. Returns the current ptr location.
*/
char	*find_key_end(char *ptr)
{
	if (ft_isalpha(*ptr) || *ptr == '_')
	{
		while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
			ptr++;
	}
	else if (*ptr == '?' || (*ptr >= '0' && *ptr <= '9'))
		ptr++;
	return (ptr);
}

/*
Forms a string from the given point. If the first character is the variable 
symbol $, string end is specified by the find_key_end function. Otherwise 
string end is the $ symbol or the end of the string. The new substring is 
added to the end of the expander->str_list.
*/
int	cut_str(t_expander *expander)
{
	char	*temp;
	t_str	*node;

	expander->start = expander->ptr++;
	if (*expander->start == '$')
		expander->ptr = find_key_end(expander->ptr);
	else
	{
		while (*expander->ptr && *expander->ptr != '$')
			expander->ptr++;
	}
	temp = ft_substr(expander->start, 0, expander->ptr - expander->start);
	if (!temp)
		return (ERROR);
	node = str_new(temp);
	if (!node)
	{
		free(temp);
		return (ERROR);
	}
	str_add_back(&expander->str_list, node);
	return (SUCCESS);
}

/*
Returns an allocated string consisting of:
a. given var's value, if var exists
b. previous commands exit status for $?
c. "" empty string for anything else
*/
static char	*expand_var(t_var *var, int prev_status)
{
	if (var)
		return (ft_strdup(var->value));
	else if (*(var->value + 1) == '?')
		return (ft_itoa(prev_status));
	else
		return (ft_strdup(""));
}

/*
Expands any variable strings in the str_list. For variables not enclosed in 
double quotes, any additional whitespace within the returned variable content 
is condensed into single spaces.*/
int	expand_strings(t_expander *expander, t_data *data)
{	
	char	*temp;
	t_str	*node;
	t_var	*var;

	node = expander->str_list;
	while (node)
	{
		if (*node->str == '$' && *(node->str + 1))
		{
			var = var_get_var(data->envp_list, node->str + 1);
			temp = expand_var(var, data->prev_status);
			if (!temp)
				return (ERROR);
			if (!expander->quote && splitjoin(&temp, " \t\v\n\r\f", " "))
				return (ERROR);
			free(node->str);
			node->str = temp;
		}
		node = node->next;
	}
	return (SUCCESS);
}
