/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:06:26 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:26:01 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *arr, int c, size_t len)
{
	unsigned char	*p;

	p = arr;
	while (len > 0)
	{
		*p = c;
		p++;
		len--;
	}
	return (arr);
}
