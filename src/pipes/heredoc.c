/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/26 14:16:05 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Writes a line to the heredoc pipe. Expands variables if necessary.
 *
 * This function writes the given line to the heredoc pipe. If the line
 * is not quoted or uses double quotes, it expands variables before writing.
 */
static void	write_line_to_pipe(char *line, int fd, t_tkn_quote q, t_shell *sh)
{
	char	*expanded;

	if (q == Q_NONE)
	{
		expanded = expand_var_value(line, sh);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

/**
 * Fills the heredoc pipe with input from the user.
 *
 * This function continuously reads input from the user until the delimiter
 * is encountered. The lines are written to the pipe. If EOF or Ctrl+D is
 * detected, the process exits.
 */
static void	fill_hd_pipe(int fd, const char *delim, t_shell *sh, t_tkn_quote q)
{
	char	*line;

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
		write_line_to_pipe(line, fd, q, sh);
		free(line);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

/**
 * Closes the pipe and waits for the heredoc child process to finish.
 *
 * After the child process that handles the heredoc input terminates,
 * this function checks the exit status, handles potential signals like SIGINT,
 * and returns the pipe descriptor for reading.
 */
void	close_pip_and_wait(int *pipefd, t_redir *redir, t_shell *sh, pid_t pid)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		sh->exit_status = 130;
		g_exit_status = 130;
		redir->fd = -1;
	}
	else if (WIFEXITED(status))
		redir->fd = dup(pipefd[0]);
	else
		redir->fd = -1;
	close(pipefd[0]);
}

/**
 * Creates a pipe for heredoc input & forks a child process to handle the input.
 *
 * The parent process waits for the child process to handle the heredoc input
 * and returns the read end of the pipe if successful. The child process reads
 * input from the user until the delimiter is entered.
 */
static void	create_heredoc_pipe(t_redir *redir, t_shell *sh)
{
	int		pipefd[2];
	pid_t	pid;

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
		fill_hd_pipe(pipefd[1], redir->delimiter, sh, redir->delim_quote);
	}
	else
		close_pip_and_wait(pipefd, redir, sh, pid);
}

/**
 * Processes all heredoc redirections in the given command.
 *
 * This function loops through all redirections in the command and calls
 * `create_heredoc_pipe()` for each heredoc redirection found.
 */
void	handle_heredoc(t_cmd *cmd, t_shell *sh)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				create_heredoc_pipe(redir, sh);
				if (redir->fd == -1)
					return ;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
