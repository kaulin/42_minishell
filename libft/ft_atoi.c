/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:53:44 by kkauhane          #+#    #+#             */
/*   Updated: 2024/02/14 12:33:06 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	error(long int result)
{
	if (result < INT_MIN || result > INT_MAX)
	{
		write(2, "Error\n", 6);
		exit (1);
	}
	return (result);
}

static int	count_signs(const char *s, int i)
{
	if ((s[i] == 43 || s[i] == 45) && (s[i + 1] == 43 || s[i + 1] == 45))
		return (0);
	if (s[i] == 45)
		return (1);
	if (s[i] == 43)
		return (2);
	return (3);
}

int	ft_atoi(const char *str)
{
	int			signs;
	long int	result;
	int			i;
	long int	prev;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	signs = count_signs(str, i);
	if (signs == 0)
		return (0);
	if (signs == 1 || signs == 2)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		prev = result;
		result = error(result * 10 + (str[i] - 48));
		i++;
		if (prev > result)
			return (-1);
	}
	if (signs == 1)
		result = result * -1;
	return (error(result));
}
