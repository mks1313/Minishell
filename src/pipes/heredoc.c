/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 13:28:24 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_heredoc_file(t_redir *redir, t_shell *shell)
{
	char	*line;
	int		fd;
	char	tmp_name[64];
	t_tkn	*temp_token;

	snprintf(tmp_name, sizeof(tmp_name), "/tmp/.heredoc_%d", getpid());
	fd = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("heredoc: open");
		return ;
	}
	free(redir->file);
	redir->file = ft_strdup(tmp_name);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (redir->delimiter && ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			break ;
		}
		temp_token = malloc(sizeof(t_tkn));
		temp_token->value = line;
		temp_token->next = NULL;
		temp_token->s_quote = 0;
		expand_variable(shell);
		expand_variable(shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

/**
 * Iterar sobre los elementos
 * Iterar sobre las redirecciones del comando
 * Si la redirección es un heredoc
 * Llamar a la función para crear el archivo heredoc
 * Avanzar a la siguiente redirección
 * Avanzar al siguiente comando
 */
void	handle_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_redir	*r;

	while (cmd)
	{
		r = cmd->redirs;
		while (r)
		{
			if (r->type == REDIR_HEREDOC)
				create_heredoc_file(r, shell);
			r = r->next;
		}
		cmd = cmd->next;
	}
}
