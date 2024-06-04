/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitjoin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:11:35 by jajuntti          #+#    #+#             */
/*   Updated: 2024/06/04 09:21:06 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
Frees a null terminated array of strings.
*/
static void	clean_array(char **array)
{
	while (*array)
		free((*array)++);
	free (array);
}

/*
Joins the elements of a given null terminated string array into a single 
string using spaces to separate elements.
*/
static char	*join_array(char **array, char *sep)
{
	int		i;
	char	*temp1;
	char	*temp2;

	i = 0;
	temp1 = ft_strdup(array[i]);
	if (!temp1)
		return (NULL);
	while (array[i] && array[i + 1])
	{
		temp2 = ft_strjoin(temp1, sep);
		free (temp1);
		if (!temp2)
			return (NULL);
		temp1 = ft_strjoin(temp2, array[i + 1]);
		free(temp2);
		if (!temp1)
			return (NULL);
	}
	return (temp1);
}

/*
Splits a string using given characters as delimiters and reconstructs 
it using the given string as a separator.
*/
int	splitjoin(char **str, char *delim, char *sep)
{
	char	*temp;
	char	**array;

	array = ft_split(*str, delim);
	if (!array)
		return (1);
	temp = join_array(array, " ");
	clean_array(array);
	if (!temp)
		return (1);
	free (*str);
	*str = temp;
	return (0);
}
