/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:00:56 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/06 08:48:27 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_i;
	size_t	n_i;

	h_i = 0;
	n_i = 0;
	if (len > ft_strlen(haystack))
		len = ft_strlen(haystack);
	if (!needle[n_i])
		return ((char *)haystack);
	while (h_i < len)
	{
		while (h_i + n_i < len && haystack[h_i + n_i] == needle[n_i])
			n_i++;
		if (!needle[n_i])
			return ((char *)haystack + h_i);
		n_i = 0;
		h_i++;
	}
	return (NULL);
}
