/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:51:56 by kkauhane          #+#    #+#             */
/*   Updated: 2024/06/10 14:24:44 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Free's the elements of an array of strings and then the array pointer itself.
*/
void	clean_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

/*
Returns 1 if given path is a directory and 0 if it's not.
*/
int	is_directory(char *filepath)
{
	int	fd;

	fd = open(filepath, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

/*
Frees an array of srings and a string given as arguments and returns the given
integer value.
*/
int	clean_return(char **arr, char *str, int ret)
{
	if (arr)
		clean_array(arr);
	if (str)
		free(str);
	return (ret);
}