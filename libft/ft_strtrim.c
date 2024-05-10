/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:46:43 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/08 12:44:36 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim_or_not(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

static char	*fill_new_string(char *newstring, char *string, int start, int end)
{
	int	j;

	j = 0;
	while (start < end)
	{
		newstring[j] = string[start];
		j++;
		start++;
	}
	newstring[j] = '\0';
	return (newstring);
}

static char	*make_new_string(char *string, char *set)
{
	char	*newstring;
	int		i;
	int		start;
	int		length;

	i = 0;
	length = 0;
	while (trim_or_not(string[i], set) == 0 && string[i] != '\0')
		i++;
	start = i;
	if (start >= (int)ft_strlen(string))
		return (ft_strdup(""));
	i = (int)ft_strlen(string) - 1;
	while (trim_or_not(string[i], set) == 0)
		i--;
	i += 1;
	length = ft_strlen(string) - start - (ft_strlen(string) - i);
	newstring = (char *)malloc(length + 1 * sizeof(char));
	if (!newstring)
		return (0);
	fill_new_string(newstring, string, start, i);
	return (newstring);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstring;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	if (!s1 && !set)
		return (0);
	newstring = make_new_string((char *)s1, (char *)set);
	if (!newstring)
		return (0);
	return (newstring);
}
