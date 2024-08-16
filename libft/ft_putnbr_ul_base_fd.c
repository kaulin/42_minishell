/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ul_base_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:40:52 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/06 12:37:34 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_ul_base_fd(unsigned long n, char *base, int fd)
{
	int		written;
	int		placeholder;
	size_t	base_len;

	written = 0;
	base_len = ft_strlen(base);
	if (n >= base_len)
	{
		placeholder = ft_putnbr_ul_base_fd(n / base_len, base, fd);
		if (placeholder < 0)
			return (-1);
		written += placeholder;
	}
	if (ft_putchar_fd(base[n % base_len], fd) < 0)
		return (-1);
	written++;
	return (written);
}
