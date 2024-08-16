/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:57:46 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/13 16:16:50 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
	{
		substr = ft_calloc(1, 1);
		if (substr == NULL)
			return (NULL);
	}
	else
	{
		if (len > ft_strlen(s) - start)
			len = ft_strlen(s) - start;
		substr = malloc(len + 1);
		if (substr == NULL)
			return (NULL);
		ft_strlcpy (substr, s + start, len + 1);
	}
	return (substr);
}
