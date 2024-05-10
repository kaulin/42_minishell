/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:46:27 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:25:11 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char				*st1;
	char				*st2;
	unsigned int		i;

	st1 = (char *)s1;
	st2 = (char *)s2;
	i = 0;
	if (st1 == st2 || n == 0)
		return (0);
	while (i < (n - 1) && st1[i] != '0' && st1[i] == st2[i])
		i++;
	return ((unsigned char) st1[i] - (unsigned char)st2[i]);
}
