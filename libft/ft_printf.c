/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:32:31 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/06 12:29:53 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_printer *printer)
{
	char	character;

	character = (char)va_arg(printer->params, int);
	if (ft_putchar_fd(character, 1) < 0)
		return (1);
	printer->output_count++;
	return (0);
}

int	print_s(t_printer *printer)
{
	char	*string;

	string = va_arg(printer->params, char *);
	printer->status = ft_putstr_fd(string, 1);
	if (printer->status < 0)
		return (1);
	printer->output_count += printer->status;
	return (0);
}

static int	convert(t_printer *printer)
{
	printer->source++;
	if (!ft_strchr("cspdiuxX%", *printer->source))
		return (1);
	if (*printer->source == 'c')
		printer->status = print_c(printer);
	if (*printer->source == 's')
		printer->status = print_s(printer);
	if (*printer->source == 'p')
		printer->status = print_p(printer);
	if (*printer->source == 'd' || *printer->source == 'i')
		printer->status = print_d(printer);
	if (*printer->source == 'u')
		printer->status = print_u(printer);
	if (*printer->source == 'x' || *printer->source == 'X')
		printer->status = print_x(printer);
	if (*printer->source == '%')
	{
		if (ft_putchar_fd('%', 1) < 0)
			printer->status = 1;
		else
			printer->status = 0;
		printer->output_count++;
	}
	printer->source++;
	return (printer->status);
}

int	ft_printf(const char *source, ...)
{
	t_printer	printer;

	if (!source)
		return (-1);
	printer.source = source;
	printer.output_count = 0;
	va_start(printer.params, source);
	while (*printer.source)
	{
		if (*printer.source != '%')
		{
			if (ft_putchar_fd(*printer.source, 1) < 0)
				return (-1);
			printer.source++;
			printer.output_count++;
		}
		else if (convert(&printer))
			return (-1);
	}
	va_end(printer.params);
	return (printer.output_count);
}
