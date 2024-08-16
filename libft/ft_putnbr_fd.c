/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:47:08 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/06 12:36:29 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	written;
	int	placeholder;

	written = 0;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		if (ft_putchar_fd('-', fd) < 0)
			return (-1);
		n *= -1;
		written++;
	}
	if (n >= 10)
	{
		placeholder = ft_putnbr_fd(n / 10, fd);
		if (placeholder < 0)
			return (-1);
		written += placeholder;
	}
	placeholder = n % 10 + '0';
	if (ft_putchar_fd(placeholder, fd) < 0)
		return (-1);
	written++;
	return (written);
}
