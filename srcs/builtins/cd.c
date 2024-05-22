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
int update_pwd(t_data *data, char *path)
{

}

/*
    Change the current working directory to directory given using chdir.
    Chdir changes the current working directory by passing the new path to the function. 
*/
int change_directory(t_data *data, char *path)
{
    if (chdir(path) != 0)//This doesn't change the PWD variable?
        //return error message
    else
        update_pwd(data, path);   
    return (EXIT_SUCCESS);
}

/*
CD with only a relative or absolute path
*/

int cd_builtin(t_data *data, char **cmds)
{
    char *path;

    if (cmds[2])//if there are more than 2 arguments, give errormessage "minishell: cd: too many arguments"
        return (EXIT_FAILURE);
    if (!cmds[1])//if no directory is given the value of the HOME shell variable is used.
    {
        path = getenv("HOME")//get the value of HOME variable
        change_directory(data, path);
    }
    else//if directory is supplied
    {
        if ('-')//Change directory to the previous directory(OLDPWD)
        if ('~')//return to home directory. DO WE NEED TO HANDLE '-' & '~'?
        if ()//If there is a '.' There will be no change of directory
        if ()//if there is a ".." it will change the directory up one directory
        else //change into the directory given
    }
}
