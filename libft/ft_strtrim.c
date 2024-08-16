/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:22:54 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:28 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (s1[start] && ft_strchr(set, (int)s1[start]) != NULL)
		start++;
	return (start);
}

static int	find_end(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1);
	while (end >= 0 && ft_strchr(set, (int)s1[end]) != NULL)
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	start = find_start(s1, set);
	end = find_end(s1, set);
	str = ft_substr(s1, (unsigned int)start, (size_t)(end - start + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}
