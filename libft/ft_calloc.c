/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:04:46 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/07 16:21:09 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*chunk;
	size_t	nbr;

	nbr = 0;
	if (count != 0 && (nbr - 1) / count < size)
		return (NULL);
	chunk = malloc(count * size);
	if (chunk == NULL)
		return (NULL);
	ft_bzero(chunk, count * size);
	return (chunk);
}
