/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:45:14 by jajuntti          #+#    #+#             */
/*   Updated: 2024/01/09 08:05:29 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	written;

	written = 0;
	written = write(fd, s, ft_strlen(s));
	if (written < 0)
		return (-1);
	if (write(fd, "\n", 1) < 0)
		return (-1);
	return (written + 1);
}
