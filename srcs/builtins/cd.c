/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pikkak <pikkak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:11:25 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/22 14:34:00 by pikkak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Returns a pointer to the value of the environmental variable in question
*/
char	*ft_getenv(t_data *data, char *variable)
{
	int		i;
	char	*pointer;

	i = 0;
	pointer = NULL;
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], variable, ft_strlen(variable)) \
			== 0 && data->envp[i][ft_strlen(variable)] == '=')
		{
			pointer = ft_strchr(data->envp[i], '=');
			pointer++;
			return (pointer);
		}
		i++;
	}
	return (NULL);
}

/*
	Sets the OLDPWD to the current working directory
	Sets the value of PWD to the new directory(new path)
*/
int	update_pwd(t_data *data)//we do not need a PWD variable to update OLDPWD in bash
{
	char	*old_pwd;
	char	*new_pwd;
	char	*temp;
	char	buffer[PATH_MAX];

	if (!(ft_getenv(data, "PWD")))
	{
		data->error_msg = ft_strdup(" cd: PWD not set");
		return (ERROR);
	}
	temp = ft_strjoin("OLDPWD", "=");
	old_pwd = ft_strjoin(temp, ft_getenv(data, "PWD"));
	free(temp);
	check_key(data, old_pwd);
	temp = ft_strjoin("PWD", "=");
	new_pwd = ft_strjoin(temp, getcwd(buffer, PATH_MAX));
	free(temp);
	check_key(data, new_pwd);
	return (SUCCESS);
}

/*
// 	Change the current working directory to directory given using chdir.
// 	Chdir changes the current working directory by passing the new path to the function. 
// */

int	change_directory(t_data *data, char *path)
{
	if (chdir(path) != 0) //System function (system call) that changes the current working directory.Doesn't change the PWD variable. What if this fails?
	{
		data->error_msg = ft_strdup("cd: error: No such file or directory");
		return (ERROR);
	}
	else
		update_pwd(data);
	return (SUCCESS);
}

static char	*up_one(t_data *data)
{
	char 	*path;
	char	*pointer;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		data->error_msg = ft_strdup("getcwd() error");
		return (NULL);
	}
	pointer = strrchr(cwd, '/');
	if (pointer!= NULL)
	{
		if (pointer == cwd) //if we are at root
			pointer++;
		*pointer = '\0';
		path = cwd;
	}
	return (path);
}

/*
CD with only a relative or absolute path
*/

int	cd_builtin(t_data *data, char **cmds)
{
	char	*path;

	path = NULL;
	if (cmds[2])
	{
		data->error_msg = ft_strdup("cd: too many arguments");
		return (ERROR);
	}
	if (!cmds[1] || ft_strncmp(cmds[1], "~", 2) == 0)
	{
		path = ft_getenv(data, "HOME");
		if (!path || *path == '\0' || *path == ' ') //tabs?
		{
			 data->error_msg = ft_strdup("cd: HOME not set");
			 return (ERROR);
		}
	}
	else if (ft_strncmp(cmds[1], "-", 2) == 0) //Change directory to the previous directory(OLDPWD). DOES THIS WORK YET
	{
		path = ft_getenv(data, "OLDPWD");//getenv gets the path from the original envp not from the copy
		if (!path)
		{
			data->error_msg = ft_strdup("cd: OLDPWD not set");
			return (ERROR);
		}
		
	}
	else if (ft_strncmp(cmds[1], "..", 3) == 0)//if there is a ".." it will change the directory up one directory
		path = up_one(data);
	else
		path = cmds[1];
	change_directory(data, path);
	return (SUCCESS);
}
