/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:26:53 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:25:25 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char			*newsrc;
	char			*newdst;
	unsigned int	i;

	newsrc = (char *)src;
	newdst = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (0);
	while (i < len)
	{
		newdst[i] = newsrc[i];
		i++;
	}
	return (dst);
}
