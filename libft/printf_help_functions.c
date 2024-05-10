/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:06:06 by kkauhane          #+#    #+#             */
/*   Updated: 2024/01/18 13:52:29 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	return (write(1, &c, 1));
}

int	print_str(char *string)
{
	int	i;

	i = 0;
	if (string == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (string[i] != '\0')
	{
		if (ft_printchar(string[i]) < 0)
			return (-1);
		i++;
	}
	return (i);
}
