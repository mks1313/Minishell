/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:13:48 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/08 16:36:53 by mmarinov         ###   ########.fr       */
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
		printf("🧪 Entrando a handle_redirections() para el comando: %s\n", cmd->cmd);
		fd = -1;
		if (r->type == REDIR_HEREDOC)
		{
			if (r->fd < 0)
			{
				fprintf(stderr, "🚨 redir->fd inválido (heredoc): %d\n", r->fd);
				return (-1);
			}
			printf("🔁 [HEREDOC] dup2(%d -> STDIN)\n", r->fd);
			if (dup2(r->fd, STDIN_FILENO) == -1)
			{
				perror("❌ dup2 heredoc");
				return (-1);
			}
			close(r->fd);
		}
		else if (r->type == REDIR_IN)
		{
			printf("🔁 [REDIR_IN] Abriendo %s para lectura\n", r->file);
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				return (perror(r->file), -1);
			printf("✅ dup2(%d -> STDIN)\n", fd);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("❌ dup2 input");
				close(fd);
				return (-1);
			}
			close(fd);
		}
		else if (r->type == REDIR_OUT)
		{
			printf("🔁 [REDIR_OUT] Abriendo %s para escritura (truncate)\n", r->file);
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		}
		else if (r->type == REDIR_APPEND)
		{
			printf("🔁 [REDIR_APPEND] Abriendo %s para escritura (append)\n", r->file);
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(r->file), -1);
			printf("✅ dup2(%d -> STDOUT)\n", fd);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("❌ dup2 append");
				close(fd);
				return (-1);
			}
			close(fd);
		}
		r = r->next;
	}
	return (0);
}
