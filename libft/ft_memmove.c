/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:43:45 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/04 11:55:16 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*to;
	unsigned char	*from;
	long			i;

	to = (unsigned char *)dst;
	from = (unsigned char *)src;
	if (src == dst)
		return (dst);
	if (dst > src && dst < src + len)
	{
		i = len - 1;
		while (i >= 0)
		{
			*(to + i) = *(from + i);
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
