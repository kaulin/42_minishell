/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:05:23 by kkauhane          #+#    #+#             */
/*   Updated: 2024/01/18 13:52:36 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_string(unsigned int n, int *pointer)
{
	char			*string;
	int				i;
	unsigned int	temp;

	i = 0;
	temp = n;
	while (temp != 0)
	{
		temp = temp / 16;
		i++;
	}
	string = (char *)ft_calloc(i + 1, sizeof(char));
	if (!string)
		return (0);
	*pointer = i - 1;
	return (string);
}

int	put_hex(unsigned int n, char c, char *string, int i)
{
	while (n != 0)
	{
		if ((n % 16) < 10)
			string[i] = (n % 16) + 48;
		if ((n % 16) >= 10 && c == 'x')
			string[i] = (n % 16) + 87;
		if ((n % 16) >= 10 && c == 'X')
			string[i] = (n % 16) + 55;
		n = n / 16;
		i--;
	}
	i = ft_strlen(string);
	if (print_str(string) < 0)
	{
		free(string);
		return (-1);
	}
	free(string);
	return (i);
}

int	print_hex(unsigned int n, char c)
{
	int		written;
	char	*string;
	int		*pointer;
	int		i;

	written = 0;
	pointer = &i;
	if (n == 0)
		return (ft_printchar('0'));
	string = create_string(n, pointer);
	if (!string)
		return (-1);
	written = put_hex(n, c, string, i);
	return (written);
}
