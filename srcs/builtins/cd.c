/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:11:25 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/11 10:36:11 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Sets the PWD and OLDPWD
Gets the current working directory
If PWD is unset sets OLDPWDs value as empty else sets it to PWDs value
Sets PWDs value as current working directory
*/

int	update_pwd(t_data *data)
{
	char	pwd[PATH_MAX];
	char	*temp;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		oops(data, 1, NULL, "getcwd failed");
		return (ERROR);
	}
	if (var_get_var(data->envp_list, "PWD") == NULL)
	{
		temp = ft_strjoin("OLDPWD=", "");
		var_add_var(&data->envp_list, temp);
		free(temp);
	}
	else
	{
		temp = ft_strjoin("OLDPWD=", var_get_value(data->envp_list, "PWD"));
		var_add_var(&data->envp_list, temp);
		free(temp);
	}
	temp = ft_strjoin("PWD=", pwd);
	var_add_var(&data->envp_list, temp);
	free(temp);
	return (SUCCESS);
}

/*
Change the current working directory to directory given using chdir.
Chdir changes the current working directory by passing the new path
to the function. 
*/

int	change_directory(t_data *data, char *path)
{
	/*
	if (access(path, F_OK) == -1)
		return (oops(data, CD_E, path, "No such file or directory"));
	if (is_directory(path) != 1)
		return (oops(data, CD_E, path, "Not a directory"));*/
	if (chdir(path) != 0)
		return (oops(data, CD_E, path, NULL));
	else if (update_pwd(data) || update_envp(data))
		return (ERROR);
	return (SUCCESS);
}

/*
Returns a path that contains the parent directory
of the directory we are in at the moment
*/

static char	*up_one(t_data *data)
{
	char	*path;
	char	*pointer;
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (oops(data, 1, NULL, "getcwd failed"), NULL);
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
Finds the path
*/
static int	find_path(t_data *data, char **cmds, char **path, int *flag)
{
	if (!cmds[1] || ft_strncmp(cmds[1], "~", 2) == 0)
	{
		*path = var_get_value(data->envp_list, "HOME");
		if (!*path || **path == '\0' || **path == ' ' || **path == '	')// is this checking for whitespace or just space and tab?
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
