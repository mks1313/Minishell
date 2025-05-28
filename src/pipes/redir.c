/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:13:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:53:33 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles redirection for heredoc type redirection.
 */
static int	redirect_heredoc(t_redir *r)
{
	int	tmp;

	if (r->type == REDIR_HEREDOC && r->fd == -1)
		return (0);
	if (r->fd < 0)
		return (-1);
	tmp = 0;
	if (ioctl(r->fd, FIONREAD, &tmp) == -1)
		perror("redir: invalid heredoc fd");
	if (dup2(r->fd, STDIN_FILENO) == -1)
		return (perror("dup2 heredoc"), -1);
	close(r->fd);
	return (0);
}

/**
 * Handles input redirection (from file to stdin).
 */
static int	redirect_input(t_redir *r)
{
	int	fd;

	fd = open(r->file, O_RDONLY);
	if (fd < 0)
		return (perror(r->file), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2 input"), close(fd), -1);
	close(fd);
	return (0);
}

/**
 * Handles output redirection (to file, appending or truncating).
 */
static int	redirect_output(t_redir *r, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(r->file, flags, 0644);
	if (fd < 0)
		return (perror(r->file), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/**
 * Handles both input and output redirections.
 */
static int	redirect_input_output(t_redir *in, t_redir *out)
{
	if (in)
	{
		if (in->type == REDIR_HEREDOC)
		{
			if (in->fd == -1)
				return (0);
			if (redirect_heredoc(in) < 0)
				return (-1);
		}
		else if (redirect_input(in) < 0)
			return (-1);
	}
	if (out)
	{
		if (redirect_output(out, out->type == REDIR_APPEND) < 0)
			return (-1);
	}
	return (0);
}

/**
 * Handles the redirections for input and output in a command.
 */
int	handle_redirections(t_cmd *cmd)
{
	t_redir	*r;
	t_redir	*last_in;
	t_redir	*last_out;

	r = cmd->redirs;
	last_in = NULL;
	last_out = NULL;
	while (r)
	{
		if (r->type == REDIR_HEREDOC || r->type == REDIR_IN)
			last_in = r;
		if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
			last_out = r;
		r = r->next;
	}
	return (redirect_input_output(last_in, last_out));
}
