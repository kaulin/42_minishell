/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:47:49 by jajuntti          #+#    #+#             */
/*   Updated: 2024/02/01 12:02:40 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_printer
{
	va_list		params;
	const char	*source;
	int			output_count;
	int			status;
}	t_printer;

int	print_c(t_printer *printer);
int	print_s(t_printer *printer);
int	print_p(t_printer *printer);
int	print_d(t_printer *printer);
int	print_u(t_printer *printer);
int	print_x(t_printer *printer);

#endif