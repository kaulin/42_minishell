/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:11:25 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/30 12:48:16 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
	Sets the OLDPWD to the current working directory(PWD before the change).
	Sets the value of PWD to the new directory(new path)
*/

int update_pwd(t_data *data)//aina kun vaihdamme osoitetta ensin pitaa oaivittaa old = pwd ja sitten pwd = cwd
{
	char *old_pwd;
	char *new_pwd;
	char *value;
	char *temp;
	char buffer[PATH_MAX];

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
	new_pwd = ft_strjoin(temp, getcwd(buffer, PATH_MAX));
	free(temp);
	check_key(data, new_pwd);
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

int cd_builtin(t_data *data, char **cmds)//can i get the amount of commands from the struct?
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (cmds[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR);
		return (EXIT_FAILURE);
	}
	if (!cmds[1] || ft_strncmp(cmds[1], "~", 2) == 0)//if no directory is given or '~' is given, the value of the HOME shell variable is used. iIs this expansion done in parsing?
	{
		path = getenv("HOME");
		if (!path || *path == '\0' || *path == ' ')//tabs?
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (ft_strncmp(cmds[1], "-", 2) == 0)//Change directory to the previous directory(OLDPWD). DOES NOT WORK
		{
			path = getenv("OLDPWD");
			//printf("%s\n", path);
			if (!path)
			{
				ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR);
				return (EXIT_FAILURE);
			}
		}
		// if (ft_strncmp(cmds[1], "..", 3) == 0)//if there is a ".." it will change the directory up one directory
		// {
		// 	path = 

		// }
		else
			path = cmds[1];
	}
	change_directory(data, path);
	return (EXIT_SUCCESS);
}
