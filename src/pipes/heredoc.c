/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/10 12:19:59 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_heredoc_pipe(int write_end, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			LOG_DEBUG("🚨 readline devolvió NULL\n");
			break ;
		}
		LOG_DEBUG("🟡 línea ingresada: [%s]\n", line);
		LOG_DEBUG("🟢 comparando con delimitador: [%s]\n", delimiter);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			LOG_DEBUG("✅ delimitador encontrado, cerrando heredoc\n");
			break ;
		}
		write(write_end, line, ft_strlen(line));
		write(write_end, "\n", 1);
		free(line);
	}
	close(write_end);
	LOG_DEBUG("✅ heredoc terminado y cerrado (write_end)\n");
}

static void	create_heredoc_pipe(t_redir *redir)
{
	int		pipefd[2];

	LOG_DEBUG("→ Entrando a create_heredoc_pipe() para delimitador: \
		[%s]\n", redir->delimiter);
	if (pipe(pipefd) == -1)
	{
		perror("❌ pipe");
		return ;
	}
	fill_heredoc_pipe(pipefd[1], redir->delimiter);
	redir->fd = dup(pipefd[0]);
	LOG_DEBUG("✅ heredoc listo, fd de lectura guardado: %d\n", redir->fd);
	LOG_DEBUG("🔧 heredoc fd asignado a redir %p: fd=%d, delim=%s\n",
		(void *)redir, redir->fd, redir->delimiter);

}

void	handle_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	(void)shell;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				LOG_DEBUG("📥 heredoc - cmd: %p\n", (void *)cmd);
				LOG_DEBUG("📥 heredoc - redir: %p, delim=%s\n", (void *)redir, \
					redir->delimiter);
				create_heredoc_pipe(redir);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
