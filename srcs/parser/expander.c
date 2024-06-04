/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:14:30 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/03 11:15:24 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
Find variable
*/
char	*get_var(char *key, char **envp)
{
	int		env_i;
	char	*content;

	env_i = 0;
	content = ft_strdup("");
	if (!content)
		return (NULL);
	if (!envp || !*envp)
		return  (content);
	while (envp[env_i])
	{
		if (ft_strncmp(envp[env_i], key, ft_strlen(key)) \
		&& envp[env_i][ft_strlen(key)] == '=')
		{
			content = ft_strdup(ft_strchr(envp[env_i], '=') + 1);
			return (content);
		}
		env_i++;
	}
	return (content);
}

char	*form_key(char *str)
{
	
}

/*
Expands the environment variables in the given string. Returns the expanded 
string, or NULL if errors occur.
*/
int	expand(char **str, int	i, t_data *data)
{
	t_expander	expander;

	expander_init(&expander, *str);
	if (is_quote_char(*expander.ptr))
	{
		expander.quote = expander.ptr;
		expander.ptr++;
	}
	if (expander.quote == '\'')
	{

	}
	else
	{
		
	}
}
