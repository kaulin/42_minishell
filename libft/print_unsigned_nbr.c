/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_nbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:39:49 by kkauhane          #+#    #+#             */
/*   Updated: 2024/01/18 13:52:53 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	unsigned_num_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*unsigned_itoa(unsigned int n)
{
	int		len;
	char	*string;

	len = unsigned_num_len(n);
	string = (char *)malloc((len + 1) * sizeof(char));
	if (!string)
		return (0);
	string[len] = '\0';
	while (n != 0)
	{
		string[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (string);
}

int	print_unsigned_nbr(unsigned int n)
{
	int		written;
	char	*num;

	written = 0;
	if (n == 0)
	{
		if (write(1, "0", 1) < 0)
			return (-1);
		return (1);
	}
	else
	{
		num = unsigned_itoa(n);
		if (!num)
			return (-1);
		written = ft_strlen(num);
		if (print_str(num) < 0)
		{
			free(num);
			return (-1);
		}
		free(num);
	}
	return (written);
}
