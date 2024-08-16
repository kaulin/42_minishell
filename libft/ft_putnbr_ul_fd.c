/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ul_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:40:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/06 12:17:49 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_ul_fd(unsigned long n, int fd)
{
	int	written;
	int	placeholder;

	written = 0;
	if (n >= 10)
	{
		placeholder = ft_putnbr_ul_fd(n / 10, fd);
		if (placeholder < 0)
			return (-1);
		written += placeholder;
	}
	if (ft_putchar_fd(n % 10 + '0', fd) < 0)
		return (-1);
	written++;
	return (written);
}
