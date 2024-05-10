/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:39:55 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:32:04 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		strsize;
	char	cc;

	strsize = ft_strlen(str);
	cc = (char)c;
	while (strsize >= 0)
	{
		if (str[strsize] == cc)
			return ((char *)str + strsize);
		strsize--;
	}
	return (0);
}
