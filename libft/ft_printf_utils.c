/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:21:17 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/06 12:31:40 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_d(t_printer *printer)
{
	int	number;

	number = va_arg(printer->params, int);
	printer->status = ft_putnbr_fd(number, 1);
	if (printer->status < 0)
		return (1);
	printer->output_count += printer->status;
	return (0);
}

int	print_x(t_printer *printer)
{
	unsigned long	hex;

	hex = va_arg(printer->params, unsigned int);
	if (*printer->source == 'x')
		printer->status = ft_putnbr_ul_base_fd(hex, "0123456789abcdef", 1);
	else
		printer->status = ft_putnbr_ul_base_fd(hex, "0123456789ABCDEF", 1);
	if (printer->status < 0)
		return (1);
	printer->output_count += printer->status;
	return (0);
}

int	print_p(t_printer *printer)
{
	unsigned long	pointer;

	pointer = va_arg(printer->params, unsigned long);
	printer->status = ft_putstr_fd("0x", 1);
	if (printer->status < 0)
		return (1);
	printer->output_count += printer->status;
	printer->status = ft_putnbr_ul_base_fd(pointer, "0123456789abcdef", 1);
	if (printer->status < 0)
		return (1);
	printer->output_count += printer->status;
	return (0);
}

int	print_u(t_printer *printer)
{
	unsigned long	number;

	number = va_arg(printer->params, unsigned int);
	printer->status = ft_putnbr_ul_fd(number, 1);
	if (printer->status < 0)
		return (1);
	printer->output_count += printer->status;
	return (0);
}
