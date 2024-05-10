/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:34:50 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:21:10 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate(int len)
{
	char	*string;

	string = (char *)malloc((len + 1) * sizeof(char));
	if (!string)
		return (0);
	string[0] = '0';
	return (string);
}

static int	nlen(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count++;
		nbr = -nbr;
	}
	if (nbr == 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*string;
	long	nbr;

	nbr = n;
	len = nlen(nbr);
	string = allocate(len);
	if (!string)
		return (0);
	if (nbr < 0)
		nbr = -nbr;
	i = len - 1;
	while (nbr != 0)
	{
		string[i] = ((nbr % 10) + 48);
		nbr = nbr / 10;
		i--;
	}
	if (n < 0)
		string[0] = '-';
	string[len] = '\0';
	return (string);
}
