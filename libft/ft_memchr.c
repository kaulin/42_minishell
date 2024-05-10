/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:42:54 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/19 16:18:39 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*string;
	unsigned char	newc;
	void			*pointer;

	i = 0;
	string = (unsigned char *)str;
	newc = (unsigned char)c;
	while (i < len)
	{
		if (string[i] == newc)
		{
			pointer = &string[i];
			return (pointer);
		}
		i++;
	}
	return (0);
}
