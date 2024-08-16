/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:47:38 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/13 16:13:10 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	else
		len = ft_strlen(dst);
	if (len >= dstsize)
		return (dstsize + ft_strlen(src));
	if (dstsize > 1)
	{
		while (src[i] && len + i < dstsize - 1)
		{
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = 0;
	}
	else
		dst[0] = 0;
	return (len + ft_strlen(src));
}
