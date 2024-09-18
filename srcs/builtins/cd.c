/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:11:25 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/18 11:08:27 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Sets the PWD
Gets the current working directory
Sets PWDs value as current working directory
*/
static int	update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*temp;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (oops(data, 1, NULL, "getcwd failed"));
	temp = ft_strjoin("PWD=", cwd);
	if (!temp)
		return (ERROR);
	if (var_add_var(&data->envp_list, temp))
	{
		free(temp);
		return (ERROR);
	}
	free(temp);
	temp = ft_strdup(cwd);
	if (!temp)
		return (ERROR);
	free(data->cwd);
	data->cwd = temp;
	return (SUCCESS);
}

/*
Sets the OLDPWD
If PWD is unset sets OLDPWDs value as empty else sets it to PWDs value
*/
static int	update_oldpwd(t_data *data)
{
	char	*temp;

	if (!var_get_var(data->envp_list, "PWD") \
		&& var_add_var(&data->envp_list, "OLDPWD="))
		return (ERROR);
	else
	{
		temp = ft_strjoin("OLDPWD=", var_get_value(data->envp_list, "PWD"));
		if (!temp)
			return (ERROR);
		if (var_add_var(&data->envp_list, temp))
		{
			free(temp);
			return (ERROR);
		}
		free(temp);
	}
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
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		path = ft_strdup(buffer);
	else if (var_get_value(data->envp_list, "PWD"))
		path = ft_strdup(var_get_value(data->envp_list, "PWD"));
	else if (data->cwd && *data->cwd)
		path = ft_strdup(data->cwd);
	else
	{
		oops(data, 1, NULL, "getcwd failed");
		return (NULL);
	}
	if (!path)
		return (NULL);
	pointer = ft_strrchr(path, '/');
	*pointer = '\0';
	return (path);
}

/*
Finds the path
*/
//Shoul we check the path for all whitespace or just space and tab?
static int	find_path(t_data *data, char **cmds, char **path, int *flag)
{
	if (!cmds[1] || ft_strncmp(cmds[1], "~", 2) == 0)
	{
		*path = var_get_value(data->envp_list, "HOME");
		if (!*path || **path == '\0' || **path == ' ' || **path == '	')
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
		return (oops(data, CD_E, NULL, NULL));
	if (find_path(data, cmds, &path, &flag) == 1 || !path)
		return (ERROR);
	if (chdir(path))
	{
		if (flag && path)
			free(path);
		return (oops(data, CD_E, cmds[1], NULL));
	}
	if (flag && path)
		free(path);
	if (update_oldpwd(data) || update_pwd(data) || update_envp(data))
		return (ERROR);
	return (SUCCESS);
}
