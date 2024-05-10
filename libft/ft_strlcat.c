/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:17:49 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:30:22 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	res;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	res = dstlen + srclen;
	if (size == 0 && (!src || !dst))
		return (res);
	if (dstlen > size)
		res = size + srclen;
	while (src[i] != '\0' && (dstlen + 1) < size)
	{
		dst[dstlen] = src[i];
		dstlen++;
		i++;
	}
	dst[dstlen] = '\0';
	return (res);
}
