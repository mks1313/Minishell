/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:13:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 13:06:52 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_fd(t_redir *r)
{
	// 👇 Esto es lo que agregás
	LOG_DEBUG("👶 redir recibido en exec: %p, delim=%s, fd=%d\n",
			(void *)r, r->delimiter, r->fd);
	if (r->type == REDIR_HEREDOC && r->fd == -1)
	{
		LOG_DEBUG("⚠️  Saltando heredoc sin fd asignado (redir %p)\n", \
			(void *)r);
		return (0);
	}
	if (r->fd < 0)
	{
		LOG_DEBUG("🚨 redir->fd inválido (heredoc): %d\n", r->fd);
		return (-1);
	}
	if (fcntl(r->fd, F_GETFD) == -1)
		perror("🚨 redir->fd inválido antes de dup2");
	LOG_DEBUG("🔁 [HEREDOC] dup2(%d -> STDIN)\n", r->fd);
	if (dup2(r->fd, STDIN_FILENO) == -1)
		return (perror("❌ dup2 heredoc"), -1);
	close(r->fd);
	return (0);
}

static int	handle_input(t_redir *r)
{
	int	fd;

	LOG_DEBUG("🔁 [REDIR_IN] Abriendo %s para lectura\n", r->file);
	fd = open(r->file, O_RDONLY);
	if (fd < 0)
		return (perror(r->file), -1);
	//LOG_DEBUG("✅ dup2(%d -> STDIN)\n", fd);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("❌ dup2 input"), close(fd), -1);
	close(fd);
	return (0);
}

static int	handle_output(t_redir *r, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if (append)
		LOG_DEBUG("🔁 [REDIR_APPEND] Abriendo %s para escritura (append)\n", \
			r->file);
	else
		LOG_DEBUG("🔁 [REDIR_OUT] Abriendo %s para escritura (truncate)\n", \
			r->file);
	fd = open(r->file, flags, 0644);
	if (fd < 0)
		return (perror(r->file), -1);
	LOG_DEBUG("✅ dup2(%d -> STDOUT)\n", fd);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("❌ dup2 output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redir	*r = cmd->redirs;
	t_redir	*last_in = NULL;
	t_redir	*last_out = NULL;

	while (r)
	{
		if (r->type == REDIR_HEREDOC || r->type == REDIR_IN)
			last_in = r;
		if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
			last_out = r;
		r = r->next;
	}
	if (last_in)
	{
		if (last_in->type == REDIR_HEREDOC)
		{
			if (last_in->fd == -1)
			{
				LOG_DEBUG(RED"⚠️  HEREDOC sin fd asignado, saltando redir %p\n"RES,
					(void *)last_in);
				return (0);
			}
			if (process_heredoc_fd(last_in) < 0)
				return (-1);
		}
		else if (handle_input(last_in) < 0)
			return (-1);
	}
	if (last_out)
	{
		if (handle_output(last_out, last_out->type == REDIR_APPEND) < 0)
			return (-1);
	}
	return (0);
}
