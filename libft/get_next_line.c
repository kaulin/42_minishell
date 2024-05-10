/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:31:37 by kkauhane          #+#    #+#             */
/*   Updated: 2024/02/14 13:18:03 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_gnl(char **str)
{
	free(*str);
	*str = NULL;
	return (0);
}

static char	*get_next(char *totalread)
{
	char	*newline;
	char	*pointer;
	int		length;

	pointer = ft_strchr_gnl(totalread, '\n');
	length = (pointer - totalread) + 1;
	newline = ft_substr_gnl(totalread, 0, length);
	if (!newline)
		return (NULL);
	return (newline);
}

static char	*get_remainder(char *totalread)
{
	char	*remainder;
	char	*pointer;
	int		length;

	pointer = ft_strchr_gnl(totalread, '\n');
	if (!pointer)
	{
		remainder = NULL;
		return (ft_free_gnl(&totalread));
	}
	length = (pointer - totalread) + 1;
	if (!totalread[length])
		return (ft_free_gnl(&totalread));
	remainder = ft_substr_gnl(totalread, length, ft_strlen(totalread) - length);
	if (!remainder)
		return (ft_free_gnl(&totalread));
	ft_free_gnl(&totalread);
	return (remainder);
}

static char	*read_next_line(int fd, char *totalread)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_gnl(&totalread));
	buffer[0] = '\0';
	while (i > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i > 0)
		{
			buffer[i] = '\0';
			totalread = ft_strjoin_gnl(totalread, buffer);
			if (!totalread)
				return (ft_free_gnl(&buffer));
		}
	}
	free(buffer);
	if (i == -1)
		return (ft_free_gnl(&totalread));
	return (totalread);
}

char	*get_next_line(int fd)
{
	char		*nextline;
	static char	*totalread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if ((totalread && !ft_strchr_gnl(totalread, '\n')) || !totalread)
		totalread = read_next_line(fd, totalread);
	if (!totalread)
		return (0);
	nextline = get_next(totalread);
	if (!nextline)
		return (0);
	totalread = get_remainder(totalread);
	return (nextline);
}
