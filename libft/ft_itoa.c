/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:25:45 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/06 08:15:13 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(long nbr)
{
	int	digits;

	digits = 1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		digits++;
	}
	return (digits);
}

static void	convert(int sign, int digits, long nbr, char *str)
{
	int	i;

	i = sign + digits;
	str [i--] = 0;
	if (sign)
		str[0] = '-';
	while (i >= sign)
	{
		str[i] = '0' + nbr % 10;
		nbr = nbr / 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		digits;
	int		sign;
	char	*str;

	nbr = (long)n;
	sign = 0;
	if (nbr < 0)
	{
		sign = 1;
		nbr *= -1;
	}
	digits = get_digits(nbr);
	str = malloc(sign + digits + 1);
	if (str == NULL)
		return (NULL);
	convert(sign, digits, nbr, str);
	return (str);
}
