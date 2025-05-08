/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:13:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/08 20:08:20 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_fd(t_redir *r)
{
	if (r->fd < 0)
	{
		fprintf(stderr, "🚨 redir->fd inválido (heredoc): %d\n", r->fd);
		return (-1);
	}
	printf("🔁 [HEREDOC] dup2(%d -> STDIN)\n", r->fd);
	if (dup2(r->fd, STDIN_FILENO) == -1)
		return (perror("❌ dup2 heredoc"), -1);
	close(r->fd);
	return (0);
}

static int	handle_input(t_redir *r)
{
	int	fd;

	printf("🔁 [REDIR_IN] Abriendo %s para lectura\n", r->file);
	fd = open(r->file, O_RDONLY);
	if (fd < 0)
		return (perror(r->file), -1);
	printf("✅ dup2(%d -> STDIN)\n", fd);
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
		printf("🔁 [REDIR_APPEND] Abriendo %s para escritura (append)\n", \
			r->file);
	else
		printf("🔁 [REDIR_OUT] Abriendo %s para escritura (truncate)\n", \
			r->file);
	fd = open(r->file, flags, 0644);
	if (fd < 0)
		return (perror(r->file), -1);
	printf("✅ dup2(%d -> STDOUT)\n", fd);
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
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_HEREDOC && process_heredoc_fd(r) < 0)
			return (-1);
		else if (r->type == REDIR_IN && handle_input(r) < 0)
			return (-1);
		else if (r->type == REDIR_OUT && handle_output(r, 0) < 0)
			return (-1);
		else if (r->type == REDIR_APPEND && handle_output(r, 1) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
