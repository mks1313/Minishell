/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:13:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/03 19:22:43 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		fd = -1;
		if (r->type == REDIR_IN || r->type == REDIR_HEREDOC)
			fd = open(r->file, O_RDONLY);
		else if (r->type == REDIR_OUT)
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == REDIR_APPEND)
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(r->file);
			return (-1);
		}
		if ((r->type == REDIR_IN || r->type == REDIR_HEREDOC) && dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 in");
			close(fd);
			return (-1);
		}
		else if ((r->type == REDIR_OUT || r->type == REDIR_APPEND) && dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 out");
			close(fd);
			return (-1);
		}
		close(fd);
		r = r->next;
	}
	return (0);
}

