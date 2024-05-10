/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:49:25 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:31:51 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_needle(char *haystack, char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (needle == haystack || len == 0 || needle[i] == '\0')
		return (haystack);
	if (!needle && !haystack && !len)
		return (0);
	while (haystack[i] && i < len)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return (haystack + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (len == 0 && (ft_strlen(haystack) == 0 || ft_strlen(needle)) == 0)
		return ((char *) haystack);
	if (len == 0 && ft_strlen(haystack) == 0 && ft_strlen(needle) == 0)
		return ((char *) haystack);
	if (!len)
		return (0);
	return (find_needle((char *)haystack, (char *)needle, len));
}
