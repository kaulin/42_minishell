/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:51 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/06 12:35:58 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"

// Standard FDs
# define STDIN 0
# define STDOUT 1
# define STDERR 2

// Error codes
# define SUCCESS 0
# define ERROR 1
# define SYNTAX_E 2
# define CANT_EXE_E 126
# define NO_CMD_E 127

typedef struct s_data
{
	char			*input;
	struct s_var	*envp_list;
	char			**envp_arr;
	char			**paths;
	int				o_stdin;
	int				o_stdout;
	struct s_cmd	*cmd_list;
	int				cmd_count;
	int				error_handled;
	int				status;
	int				prev_status;
}	t_data;

typedef struct s_cmd
{
	char			*path; // path to command
	char			**cmd_arr; // 0 term list of cmd and arguments
	struct s_file	*infiles; // infiles for specific cmd, NULL if not set
	struct s_file	*outfiles; // outfiles for specific cmd, NULL if not set
	int				in_fd;
	int				out_fd;
	pid_t			pid;
	struct s_cmd	*next; // pointer to next cmd in cmd_list, NULL if last
}	t_cmd;

/*
Defines struct to store command in- and outfiles. Uses vary. For infiles, flag 
indicates heredoc. If flagged, file_str is heredoc delimeter instead of file 
path. For outfiles, flag indicates appending. If flagged, outfile is appended 
on write, not overwritten.
*/
typedef struct s_file
{
	char			*file_str;
	int				flag;
	struct s_file	*next;
}	t_file;

/*
Defines struct to store environment variables in a linked list of key-value 
pairs.
*/
typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
	struct s_var	*alpha;
	struct s_var	*anext;
}	t_var;

// data.c
int		update_envp(t_data *data);
void	reset_data(t_data *data);
void	clean_data(t_data *data);
int		init_data(t_data *data, char **envp);

// error.c
int		oops(t_data *data, int e_code, char *e_file, char *e_str);

// cmd_list.c
t_cmd	*cmd_new(void);
void	cmd_add_back(t_cmd **cmd_list, t_cmd *new_cmd);
void	cmd_delone(t_cmd *cmd);
void	cmd_clear(t_cmd **cmd_list);
int		cmd_print(t_cmd *cmd);

// var_list.c
t_var	*var_new(char *key, char *value);
void	var_add_back(t_var **var_list, t_var *new);
void	var_delone(t_var *var);
void	var_clear(t_var **var_list);
char	*var_to_str(t_var *var);

// var_list_utils.c
int		var_count(t_var *var);
t_var	*var_get_var(t_var *var, char *key);
char	*var_get_value(t_var *var, char *key);
char	**var_to_arr(t_var *var_list);

// var_list_edits.c
int		var_add_var(t_var **var_list, char *str);
void	var_add_to_alpha(t_var *var, t_var *new);
void	var_remove_key(t_var **var_list, char *key);
void	var_remove_from_alpha(t_var *var, t_var *rmv);

// file_list.c
t_file	*file_new(char *content, int flag);
void	file_add_back(t_file **file_list, t_file *new_file);
void	file_delone(t_file *file);
void	file_clear(t_file **file_list);

// parser.c
int		parse(char *input, t_data *data);

// signal.c
void	sigint_handler(int signal);

// builtins
int		check_if_builtin(char **cmds);
int		exec_builtin(t_data *data, char **cmds);
int		cd_builtin(t_data *data, char **cmds);
int		pwd_builtin(t_data *data, char **cmds);
int		echo_builtin(char **cmd);
int		env_builtin(t_data *data, char **cmds);
void	exit_builtin(t_data *data);
int		unset_builtin(t_data *data, char **cmds);
int		export_builtin(t_data *data, char **cmds);

// paths.c
char	**parse_paths(t_data *data);
char	*find_cmd_path(t_data *data, char *cur_cmd);

// redirection.c
int		check_redir(t_data *data, t_cmd *cur_cmd);

// heredocs.c
int		check_heredocs(t_data *data, t_cmd *cur_cmd);

//execute.c
int		execute_and_pipe(t_data *data);

//exec_utils.c
void	reset_io(t_data *data);
int		check_file(t_data *data, t_file *cur_file, int flag);

// utils.c
int		join_print_free(char *str1, char *str2, int fd);
void	clean_array(char **array);
int		is_directory(char *filepath);

#endif