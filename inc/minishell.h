/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:51 by kkauhane          #+#    #+#             */
/*   Updated: 2024/05/14 15:38:30 by jajuntti         ###   ########.fr       */
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
	char			*path; // path to command
	char			*cmd_str; // command name (can be full path), flags and arguments
	char			*infile; // infile for specific cmd, NULL if not set
	int				heredoc_flag;
	char			*outfile; // outfile for specific cmd, NULL if not set
	int				append_flag;
	pid_t			pid;
	struct s_cmd	*next; // pointer to next cmd in cmd_list, NULL if last
}	t_cmd;

// cmd_list.h
// init node
// set node values
// add node back
// remove node
// clear list

// data.c
void	clean_data(t_data *data);
void	init_data(t_data *data, char **envp);

// parser.c
int	parse(char *input, t_data *data);

// signal.c
void	sigint_handler(int signal);

#endif