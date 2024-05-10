/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:44:20 by kkauhane          #+#    #+#             */
/*   Updated: 2024/01/18 13:51:14 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_type(char *format, va_list args, char c)
{
	size_t			i;
	int				written;

	i = 0;
	written = 0;
	if (format[i] == c && format[i + 1] == c)
		written = ft_printchar('%');
	else if (format[i] == c && format[i + 1] == 'c')
		written = ft_printchar(va_arg(args, int));
	else if (format[i] == c && format[i + 1] == 's')
		written = print_str(va_arg(args, char *));
	else if (format[i] == c && format[i + 1] == 'p')
		written = print_pointer(args);
	else if (format[i] == c && (format[i + 1] == 'd' || format[i + 1] == 'i'))
		written = print_nbr(va_arg(args, int));
	else if (format[i] == c && format[i + 1] == 'u')
		written = print_unsigned_nbr(va_arg(args, unsigned int));
	else if (format[i] == c && (format[i + 1] == 'x' || format[i + 1] == 'X'))
		written = print_hex(va_arg(args, unsigned int), format[i + 1]);
	return (written);
}

int	parse_format(char *format, char c, va_list args, int temp)
{
	int		i;
	int		written;

	i = 0;
	written = 0;
	while (format[i] != '\0')
	{
		while (format[i] != c && format[i] != '\0')
		{
			if (ft_printchar(format[i]) < 0)
				return (-1);
			written++;
			i++;
		}
		if (format[i] == c && format[i + 1] != '\0')
		{
			temp = check_type(&format[i], args, c);
			if (temp < 0)
				return (-1);
			written += temp;
			i += 2;
		}
	}
	return (written);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			written;
	char		c;
	int			temp;

	c = '%';
	temp = 0;
	va_start(args, format);
	written = parse_format((char *)format, c, args, temp);
	va_end(args);
	return (written);
}
