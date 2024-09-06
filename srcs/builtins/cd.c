/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:11:25 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/06 08:29:46 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Makes the new PWD and new OLDPWD
Sets the OLDPWD to the current working directory
Sets the value of PWD to the new directory(new path)
Calls check_key to change the variables
*/
int	update_pwd(t_data *data)
{
	char	*new_pwd;
	char	buffer[PATH_MAX];
	t_var	*var_pwd;
	t_var	*var_old;

	var_pwd = var_get_var(data->envp_list, "PWD");
	if (!var_pwd)
		return (oops(data, 1, NULL, " cd: PWD not set"));
	var_old = var_get_var(data->envp_list, "OLDPWD");
	if (!var_old)
	{
		if (var_add_var(&data->envp_list, "OLDPWD"))
			return (ERROR);
		var_old = var_get_var(data->envp_list, "OLDPWD");
	}
	new_pwd = ft_strjoin("", getcwd(buffer, PATH_MAX)); //do we need strinjoin?
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
Chdir changes the current working directory by passing the new path
to the function. 
*/

int	change_directory(t_data *data, char *path)
{
	if (chdir(path) != 0)
		return (oops(data, 1, path, "No such file or directory"));
	else if (update_pwd(data) || update_envp(data))
		return (ERROR);
	return (SUCCESS);
}

static char	*up_one(t_data *data)
{
	char	*path;
	char	*pointer;
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		oops(data, 1, NULL, "getcwd failed");
		return (NULL);
	}
	pointer = ft_strrchr(cwd, '/');
	if (pointer == cwd)
		return (path = ft_strdup(cwd));
	while (&cwd[i] != pointer)
		i++;
	path = (char *)malloc(i + 1 * sizeof(char));
	if (!path)
		return (NULL);
	i = 0;
	while (&cwd[i] != pointer)
	{
		path[i] = cwd[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

/*
Change directory to the previous directory(OLDPWD).
*/
static int	find_path(t_data *data, char **cmds, char **path, int *flag)
{
	if (!cmds[1] || ft_strncmp(cmds[1], "~", 2) == 0)
	{
		*path = var_get_value(data->envp_list, "HOME");
		if (!*path || **path == '\0' || **path == ' ' || **path == '	') // is this checking for whitespace or just space and tab?
			return (oops(data, 1, NULL, "cd: HOME not set"));
	}
	else if (ft_strncmp(cmds[1], "-", 2) == 0)
	{
		*path = var_get_value(data->envp_list, "OLDPWD");
		if (!*path)
			return (oops(data, 1, NULL, "cd: OLDPWD not set"));
	}
	else if (ft_strncmp(cmds[1], "..", 3) == 0)
	{
		*path = up_one(data);
		if (*path)
			*flag = 1;
	}
	else
		*path = cmds[1];
	return (SUCCESS);
}

/*
CD with only a relative or absolute path
*/
int	cd_builtin(t_data *data, char **cmds)
{
	char	*path;
	int		i;
	int		flag;

	path = NULL;
	i = 0;
	flag = 0;
	while (cmds[i] != NULL)
		i++;
	if (i >= 3)
		return (oops(data, 1, NULL, "cd: too many arguments"));
	if (find_path(data, cmds, &path, &flag) == 1 || !path)
		return (ERROR);
	if (change_directory(data, path) == 1)
	{
		if (flag)
			free(path);
		return (ERROR);
	}
	if (flag)
		free(path);
	return (SUCCESS);
}
