/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:28:54 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/06 08:56:32 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	ch;
	int				i;
	int				last;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	last = -1;
	while (str[i])
	{
		if (str[i] == ch)
			last = i;
		i++;
	}
	if (str[i] == ch)
		last = i;
	if (last < 0)
		return (NULL);
	return ((char *)&str[last]);
}
