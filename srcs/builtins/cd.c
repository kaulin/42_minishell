/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:11:25 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/30 14:36:12 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Makes the new PWD and new OLDPWD
	Sets the OLDPWD to the current working directory
	Sets the value of PWD to the new directory(new path)
	Calls check_key to change the variables
*/

int	update_pwd(t_data *data)//we do not need a PWD variable to update OLDPWD in bash
{
	char	*temp;
	char	*new_pwd;
	char	buffer[PATH_MAX];
	t_var	*var_pwd;
	t_var	*var_old;

	
	var_pwd = var_get_var(data->envp_list, "PWD");
	if (!var_pwd)
		return (data->error_msg = ft_strdup(" cd: PWD not set"), ERROR);
	if (var_add_var(&data->envp_list, "OLDPWD"))
		return (ERROR);
	var_old = var_get_var(data->envp_list, "OLDPWD");
	temp = ft_strjoin("PWD", "=");
	if (!temp)
		return (ERROR);
	new_pwd = ft_strjoin(temp, getcwd(buffer, PATH_MAX));//this makes the new PWD that is put into the list
	free(temp);
	if (!new_pwd)
		return (ERROR);
	if (var_old->value)
		free(var_old->value);
	var_old->value = var_pwd->value;
	var_pwd->value = new_pwd;
	return (SUCCESS);
}

/*
 	Change the current working directory to directory given using chdir.
 	Chdir changes the current working directory by passing the new path to the function. 
 */

int	change_directory(t_data *data, char *path)
{
	if (chdir(path) != 0) //System function (system call) that changes the current working directory. Doesn't change the PWD variable. What if this fails?
		return (data->error_msg = ft_strdup("cd: error: No such file or directory"), ERROR);
	else
	{
		if (update_pwd(data) || update_envp(data))
			return (ERROR);
	}
	return (SUCCESS);
}

static char *up_one(t_data *data) 
{
	char *path;
	char *pointer;
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (data->error_msg = ft_strdup("getcwd() error"), NULL);
	pointer = strrchr(cwd, '/');
	if (pointer != NULL) 
	{
		if (pointer == cwd) // if we are at root
			pointer++;
		*pointer = '\0';
	}
	path = strdup(cwd);
	if (!path)
	{
		data->error_msg = ft_strdup("Memory allocation failed");
		return (NULL);
	}
	return (path);
}

/*
CD with only a relative or absolute path
*/
int	cd_builtin(t_data *data, char **cmds)
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (cmds[i] != NULL)
		i++;
	if (i >= 3)
		return (data->error_msg = ft_strdup("cd: too many arguments"), ERROR);
	if (!cmds[1] || ft_strncmp(cmds[1], "~", 2) == 0)
	{
		path = var_get_value(data->envp_list, "HOME");
		if (!path || *path == '\0' || *path == ' ') //tabs?
			 return (data->error_msg = ft_strdup("cd: HOME not set"), ERROR);
	}
	else if (ft_strncmp(cmds[1], "-", 2) == 0) //Change directory to the previous directory(OLDPWD).
	{
		path = var_get_value(data->envp_list, "OLDPWD");
		if (!path)
			return (data->error_msg = ft_strdup("cd: OLDPWD not set"), ERROR);
	}
	else if (ft_strncmp(cmds[1], "..", 3) == 0)//if there is a ".." it will change the directory up one directory
		path = up_one(data);
	else
		path = cmds[1];//path is the path given
	return (change_directory(data, path));
}
