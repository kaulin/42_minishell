/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:39:19 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/06 12:56:32 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char *dstr)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(dstr, s[i]) != NULL)
			i++;
		if (s[i] && ft_strchr(dstr, s[i]) == NULL)
		{
			count++;
			while (s[i] && ft_strchr(dstr, s[i]) == NULL)
				i++;
		}
	}
	return (count);
}

static int	make_word(char **dest, char const *src, char *dstr)
{
	size_t	i;

	i = 0;
	while (ft_strchr(dstr, src[i]) == NULL && src[i] != 0)
		i++;
	*dest = ft_substr(src, 0, i);
	return ((int)i);
}

static void	*make_words(char **array, int count, char const *s, char *dstr)
{
	int	str_i;
	int	word_i;

	str_i = 0;
	word_i = 0;
	while (s[str_i])
	{
		if (ft_strchr(dstr, s[str_i]) == NULL)
		{
			str_i += make_word(&array[word_i], s + str_i, dstr);
			if (array[word_i] == NULL)
				return (NULL);
			word_i++;
		}
		else
			str_i++;
	}
	array[count] = NULL;
	return (array);
}

static void	clean(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
}

char	**ft_split(char const *s, char *dstr)
{
	int		count;
	char	**array;

	count = count_words(s, dstr);
	array = malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	if (make_words(array, count, s, dstr) == NULL)
	{
		clean(array);
		free(array);
		return (NULL);
	}
	return (array);
}
