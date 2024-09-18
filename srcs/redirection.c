/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:31:52 by kkauhane          #+#    #+#             */
/*   Updated: 2024/09/18 12:33:50 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handles input redirection
*/

static int	redir_in(t_data *data, t_cmd *cur_cmd, t_redir *redir)
{
	if (redir->type == HEREDOC)
		cur_cmd->in_fd = cur_cmd->heredoc_fd;
	else
		cur_cmd->in_fd = open(redir->file_str, O_RDONLY);
	if (dup2(cur_cmd->in_fd, STDIN_FILENO) == -1)
		return (oops(data, 1, NULL, "dup2 failed\n"));
	close(cur_cmd->in_fd);
	return (SUCCESS);
}

/*
Handles output redirection
*/
static int	redir_out(t_data *data, t_cmd *cur_cmd, t_redir *redir)
{
	if (redir->type == APPEND)
		cur_cmd->out_fd = open(redir->file_str, \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		cur_cmd->out_fd = open(redir->file_str, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cur_cmd->out_fd == -1)
		return (oops(data, 1, redir->file_str, "Permission denied"));
	return (SUCCESS);
}

/*
Checks if there is a redirection and if it is in input or output.
*/
int	check_redir(t_data *data, t_cmd *cur_cmd)
{
	t_redir	*redir;
	t_redir	*last_in;
	t_redir	*last_out;

	last_in = NULL;
	last_out = NULL;
	redir = cur_cmd->redirects;
	while (redir)
	{
		if (check_file(data, redir))
			return (ERROR);
		if (redir->type == INFILE || redir->type == HEREDOC)
			last_in = redir;
		else if (redir->type == OUTFILE || redir->type == APPEND)
			last_out = redir;
		redir = redir->next;
	}
	if (last_in && redir_in(data, cur_cmd, last_in))
		return (ERROR);
	if (last_out && redir_out(data, cur_cmd, last_out))
		return (ERROR);
	return (SUCCESS);
}
