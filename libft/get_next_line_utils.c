/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:31:48 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/06 16:53:35 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(char *str, int c)
{
	int		i;
	char	*pointer;
	char	cc;

	i = 0;
	pointer = 0;
	cc = (char)c;
	while (str[i] != cc && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == cc)
	{
		pointer = &str[i];
		return (pointer);
	}
	return (0);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	i = 0;
	sub = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		sub = malloc(sizeof(char) * (1));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while ((len) > i && s[start] != '\0')
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup_gnl(char *s1)
{
	char	*copy;
	int		i;

	copy = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!copy)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (0);
	}
	newstr = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	if (!newstr)
		return (ft_free_gnl(&s1));
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}
