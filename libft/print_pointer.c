/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:24:29 by kkauhane          #+#    #+#             */
/*   Updated: 2024/01/18 13:52:46 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ptr_len(unsigned long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

int	put_ptr(unsigned long pointer)
{
	if (pointer >= 16)
	{
		put_ptr(pointer / 16);
		put_ptr(pointer % 16);
	}
	else
	{
		if (pointer <= 9)
		{
			if (ft_printchar(pointer + '0') < 0)
				return (-1);
		}
		else
		{
			if (ft_printchar(pointer - 10 + 'a') < 0)
				return (-1);
		}
	}
	return (1);
}

int	print_pointer(va_list args)
{
	unsigned long	pointer;
	int				written;

	pointer = (unsigned long)va_arg(args, unsigned long);
	if (pointer == 0)
	{
		if (write (1, "0x0", 3) < 0)
			return (-1);
		return (3);
	}
	if (write(1, "0x", 2) < 0)
		return (-1);
	written = 2;
	put_ptr(pointer);
	written += ptr_len(pointer);
	return (written);
}
