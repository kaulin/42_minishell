/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:51 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/14 10:34:18 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> //
# include <sys/ioctl.h>
# include <termios.h> //contains the definitions used by the terminal I/O interfaces
# include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_data
{
	char			**envp;
	struct s_cmd	*cmd_list;
	int				status;
	char			*error_msg;
}	t_data;

typedef struct s_cmd
{
	char			*path;
	char			*cmd_str;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

// data.c
void	clean_data(t_data *data);
void	init_data(t_data *data, char **envp);

// parser.c
int	parse(char *input, t_data *data);

// signal.c
void	sigint_handler(int signal);

#endif