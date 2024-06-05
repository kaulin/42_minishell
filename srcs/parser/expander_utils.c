/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:59:05 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/05 10:36:40 by jajuntti         ###   ########.fr       */
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

/*
Takes a pointer to a heap allocated string, makes a substring of it with int n 
characters trimmed from both ends, frees original string and replaces its 
pointer with the substring. If more characters would be trimmed than there are 
in the string, an empty string is used.
*/
int	trim_n(char **str, unsigned int n)
{
	char *temp;

	if (n * 2 >= ft_strlen(*str))
		temp = ft_strdup("");
	else
		temp = ft_substr(*str, n, ft_strlen(*str) - 2 * n);
	if (!temp)
		return (ERROR);
	free(*str);
	*str = temp;
	return (SUCCESS);
}