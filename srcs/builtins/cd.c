/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:11:25 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/13 14:28:25 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
	Sets the OLDPWD to the current working directory(PWD before the change).
	Sets the value of PWD to the new directory(new path)
*/

int update_pwd(t_data *data)
{
	char *old_pwd;
	char *new_pwd;
	char *value;
	char *temp;

	value = getenv("PWD");
	if (!value)
	{
		ft_putendl_fd("minishell: cd: PWD not set", STDERR);
		return (EXIT_FAILURE);
	}
	temp = ft_strjoin("OLDPWD", "=");
	old_pwd = ft_strjoin(temp, value);
	free(temp);
	check_key(data, old_pwd);
	value = getcwd(value, PATH_MAX);//can this fail?
	temp = ft_strjoin("PWD", "=");
	new_pwd = ft_strjoin(temp, value);
	free(temp);
	check_key(data, new_pwd);
	//free(key_value_pair);//do we ever free this?
	return (EXIT_SUCCESS);
}

/*
// 	Change the current working directory to directory given using chdir.
// 	Chdir changes the current working directory by passing the new path to the function. 
// */

int change_directory(t_data *data, char *path)
{
	if (chdir(path) != 0)//System function (system call) that changes the current working directory.Doesn't change the PWD variable. What if this fails?
	{
		ft_putendl_fd("minishell: cd: error: No such file or directory", STDERR);
		return (EXIT_FAILURE);
	}
	else
		update_pwd(data);
	return (EXIT_SUCCESS);
}

/*
CD with only a relative or absolute path
*/

int cd_builtin(t_data *data, char **cmds)//can i get the amount of commands from the parsing?
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (cmds[i])
		i++;
	if (i > 2)//if there are more than 2 arguments, give errormessage "minishell: cd: too many arguments"
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR);
		return (EXIT_FAILURE);
	}
	if (!cmds[1])//if no directory is given the value of the HOME shell variable is used.
	{
		path = getenv("HOME");//get the value of the HOME variable
		if (!path || *path == '\0' || *path == ' ')//tabs?
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR);
			return (EXIT_FAILURE);
		}
	}
	else//if path is supplied
		path = cmds[1];
	// {
	// 	if ('-')////Change directory to the previous directory(OLDPWD)
	// 	if ('~')//return to home directory. DO WE NEED TO HANDLE '-' & '~'?
	// 	if ()//If there is a '.' There will be no change of directory
	// 	if ()//if there is a ".." it will change the directory up one directory
	// 	else //change into the directory given
	// 	change_directory(data, cmpd[1]);
	// }
	change_directory(data, path);
	return (EXIT_SUCCESS);
}
