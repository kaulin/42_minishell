/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:14:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/05 11:48:19 by jajuntti         ###   ########.fr       */
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
static void	expander_init(t_expander *expander, char *str)
{
	expander->quote = 0;
	if (is_quote_char(*str))
		expander->quote = *str;
	expander->ptr = str;
	expander->var = NULL;
	expander->str_list = NULL;
	expander->temp_str = NULL;
}

/*
Traverses the given string. If the first character is alphabetic, continues as 
long as the characters are alphanumeric. If the first character is numeric, only jumps one character ahead. Returns the current ptr location.
*/
static char	*find_key_end(char *ptr)
{
	if (ft_isalpha(*ptr))
	{
		while (*ptr && ft_isalnum(*ptr))
			ptr++;
	}
	else if (*ptr >= '0' && *ptr <= '9')
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

	expander->start = expander->ptr++;
	while (*expander->ptr)
	{
		if (*expander->start == '$')
			expander->ptr = find_key_end(expander->ptr);
		else if (*expander->start != '$' && *expander->ptr == '$')
			break ;
		else
			expander->ptr++;
	}
	temp = ft_substr(expander->start, 0, expander->ptr - expander->start);
	if (!temp)
		return (ERROR);
	expander->temp_str = str_new(temp);
	free(temp);
	if (!expander->temp_str)
		return (ERROR);
	str_add_back(&expander->str_list, expander->temp_str);
	return (SUCCESS);
}

/*
Expands any variable strings in the str_list. For variables not enclosed in 
double quotes, any additional whitespace within the returned variable content 
is condensed into single spaces.*/
static int	expand_strings(t_expander *expander, t_data *data)
{	
	char	*temp;

	expander->temp_str = expander->str_list;
	while (expander->temp_str)
	{
		if (*expander->temp_str->str == '$')
		{
			temp = get_var(expander->temp_str->str + 1, data->envp);
			if (!temp)
				return (ERROR);
			if (!expander->quote && splitjoin(&temp, " \t\v\n\r\f", " "))
				return (ERROR);
			free (expander->temp_str->str);
			expander->temp_str->str = temp;
		}
		expander->temp_str = expander->temp_str->next;
	}
	return (SUCCESS);
}

/*
Expands the environment variables in the given string. Returns the expanded 
string, or NULL if errors occur.
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
