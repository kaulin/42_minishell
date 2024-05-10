/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:07:20 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/17 15:38:29 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t length, size_t size)
{
	char			*string;
	unsigned int	i;

	i = 0;
	if (length > 0 && size > 0 \
			&& ((length * size % size != 0 || length * size % length != 0)))
		return (0);
	if (length * size > UINT_MAX)
		return (0);
	string = malloc(length * size);
	if (!string)
		return (0);
	while (i < (length * size))
	{
		string[i] = 0;
		i++;
	}
	return (string);
}
