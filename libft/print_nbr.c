/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:03:07 by kkauhane          #+#    #+#             */
/*   Updated: 2024/01/18 13:52:41 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	numcount(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	if (n < 0)
	{
		if (ft_printchar('-') < 0)
			return (-1);
		n *= -1 ;
	}
	if (n > 9)
	{
		if (ft_putnbr((n / 10)) < 0)
			return (-1);
		if (ft_printchar((n % 10 + 48)) < 0)
			return (-1);
	}
	else
	{
		if (ft_printchar(n + 48) < 0)
			return (-1);
	}
	return (1);
}

int	print_nbr(int n)
{
	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) < 0)
			return (-1);
		return (11);
	}
	else if (n == 2147483647)
	{
		if (write(1, "2147483647", 10) < 0)
			return (-1);
		return (10);
	}
	if (ft_putnbr(n) < 0)
		return (-1);
	return (numcount(n));
}
