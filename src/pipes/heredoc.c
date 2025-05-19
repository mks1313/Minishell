/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 10:08:42 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_hd_pipe(int fd, const char *delim, t_shell *sh, t_tkn_quote q)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(fd);
			exit(1);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (q == Q_NONE || q == Q_DOUBLE || q == Q_MIX)
		{
			expanded = expand_var_value(line, sh);
			write(fd, expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
			write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

static void	create_heredoc_pipe(t_redir *redir, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(pipefd[0]);
		fill_hd_pipe(pipefd[1], redir->delimiter, shell, redir->delim_quote);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_status = 130;
		redir->fd = -1;
	}
	else if (WIFEXITED(status))
		redir->fd = dup(pipefd[0]);
	else
		redir->fd = -1;
	close(pipefd[0]);
}

void	handle_heredoc(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				create_heredoc_pipe(redir, shell);
			if (redir->fd == -1)
				return ;
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
