/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:00:35 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/15 16:26:56 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 2147483647)
		write(fd, "2147483647", 10);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1 ;
		}
		if (n > 9)
		{
			ft_putnbr_fd((n / 10), fd);
			ft_putchar_fd((n % 10 + 48), fd);
		}
		else
			ft_putchar_fd(n + 48, fd);
	}
}
