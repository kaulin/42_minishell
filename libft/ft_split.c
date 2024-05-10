/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:26:57 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/08 13:10:03 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(char const *s, char delimiter)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (*s != '\0')
	{
		if (*s != delimiter && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*s == delimiter)
			i = 0;
		s++;
	}
	return (count);
}

static void	fill_array(char *array, int start, int end, char const *s)
{
	int		i;

	i = 0;
	while (start < end)
	{
		array[i] = s[start];
		start++;
		i++;
	}
	array[i] = '\0';
}

static char	**ft_free(char **string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
	return (0);
}

static char	**allocate_words(char **array, char const *s, char c)
{
	unsigned int	j;
	int				start;
	int				i;

	j = 0;
	i = 0;
	start = 0;
	while (j < ft_strlen(s))
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		if (s[j] == '\0')
			return (array);
		start = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		array[i] = (char *)malloc((j - start + 1) * sizeof(char));
		if (!array[i])
			return (ft_free(array));
		fill_array(array[i], start, j, s);
		i++;
	}
	return (array);
}

char	**ft_split(char *s, char c)
{
	char	**strarray;

	strarray = (char **)ft_calloc((wordcount(s, c) + 1), sizeof(char *));
	if (!strarray)
		return (0);
	strarray = allocate_words(strarray, s, c);
	if (!strarray)
		return (0);
	free(s);
	return (strarray);
}
