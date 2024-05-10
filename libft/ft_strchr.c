/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:31:12 by kkauhane          #+#    #+#             */
/*   Updated: 2023/11/19 16:19:55 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(char *str, int c)
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
