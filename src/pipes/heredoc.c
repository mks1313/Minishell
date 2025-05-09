/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/09 12:27:25 by mmarinov         ###   ########.fr       */
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
			printf("🚨 readline devolvió NULL\n");
			break ;
		}
		printf("🟡 línea ingresada: [%s]\n", line);
		printf("🟢 comparando con delimitador: [%s]\n", delimiter);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			printf("✅ delimitador encontrado, cerrando heredoc\n");
			break ;
		}
		write(write_end, line, ft_strlen(line));
		write(write_end, "\n", 1);
		free(line);
	}
	close(write_end);
	printf("✅ heredoc terminado y cerrado (write_end)\n");
}

static void	create_heredoc_pipe(t_redir *redir)
{
	int		pipefd[2];

	printf("→ Entrando a create_heredoc_pipe() para delimitador: \
		[%s]\n", redir->delimiter);
	if (pipe(pipefd) == -1)
	{
		perror("❌ pipe");
		return ;
	}
	fill_heredoc_pipe(pipefd[1], redir->delimiter);
	redir->fd = dup(pipefd[0]);
	printf("✅ heredoc listo, fd de lectura guardado: %d\n", redir->fd);
	printf("🔧 heredoc fd asignado a redir %p: fd=%d, delim=%s\n",
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
				printf("📥 heredoc - cmd: %p\n", (void *)cmd);
				printf("📥 heredoc - redir: %p, delim=%s\n", (void *)redir, \
					redir->delimiter);
				create_heredoc_pipe(redir);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
