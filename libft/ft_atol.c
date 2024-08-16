/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:39:44 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/04 15:12:06 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(" \t\v\n\r\f", str[i]) != NULL)
		i++;
	return (i);
}

long int	ft_atol(const char *str)
{
	long	num;
	long	prev;
	int		i;
	int		sign;

	i = skip_whitespace(str);
	num = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		prev = num;
		num = num * 10 + (long)str[i++] - '0';
		if (prev > num)
		{
			if (sign == 1)
				return (9223372036854775807);
			return (-9223372036854775807);
		}
	}
	return (sign * num);
}
