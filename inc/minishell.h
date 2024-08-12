/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:51 by kkauhane          #+#    #+#             */
/*   Updated: 2024/08/12 09:50:34 by jajuntti         ###   ########.fr       */
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
# include <sys/wait.h>
# include <termios.h> //contains the definitions used by the terminal I/O interfaces
# include <fcntl.h>
# include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SUCCESS 0
# define ERROR 1

typedef struct s_data
{
	char			**envp;
	char			**paths;
	int				envp_count;
	struct s_cmd	*cmd_list;
	int				status;
	char			*error_msg;
}	t_data;

typedef struct s_cmd
{
	char			*path; // path to command
	char			*cmd_str; // command name (can be full path), flags and arguments
	char			**cmd_arr; // cmd_str broken into array with split
	char			*infile; // infile for specific cmd, NULL if not set
	int				heredoc_flag;
	char			*outfile; // outfile for specific cmd, NULL if not set
	int				append_flag;
	int				in_fd;
	int				out_fd;
	pid_t			pid;
	struct s_cmd	*next; // pointer to next cmd in cmd_list, NULL if last
}	t_cmd;

// data.c
void	clean_data(t_data *data);
void	init_data(t_data *data, char **envp);
char	**copy_envp(t_data *data, char **envp);

// fail.c
void	fail(int exit_code, char *msg, t_data *data);

// cmd_list.c
t_cmd	*cmd_new(char *content);
void	cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd);
void	cmd_delone(t_cmd *cmd);
void	cmd_clear(t_cmd **cmd_list);

// parser.c
int		parse(char *input, t_data *data);

// signal.c
void	sigint_handler(int signal);

// builtins
int		check_if_builtin(char **cmds);
void	execute_builtin(t_data *data, char **cmds);
int		cd_builtin(t_data *data, char **cmds);
int 	pwd_builtin(char **cmds);
int		echo_builtin(char **cmd);
int		env_builtin(t_data *data, char **cmds);
int		env_in_order(t_data *data);
int		unset_builtin(t_data *data, char **cmds);
int		export_builtin(t_data *data, char **cmds);
int		check_key(t_data *data, char *cmd);

//paths.c
void	parse_paths(t_data *data);
char	*find_cmd_path(t_data *data, char *cur_cmd);

//redirection.c
void	check_redirection(t_data *data, t_cmd *cur_cmd);

//utils.c
int		join_print_free(char *str1, char *str2, int fd);
void	clean_array(char **array);
int		clean_return(char **arr, char *str, int ret);
int		is_directory(char *filepath);

#endif