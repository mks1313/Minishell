/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/22 14:59:55 by mmarinov         ###   ########.fr       */
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

	LOG_DEBUG("Writing line to pipe: [%s], quote=%s\n", line, quote_type_str(q));
	if (q == Q_NONE || q == Q_DOUBLE || q == Q_MIX)
	{
		expanded = expand_var_value(line, sh);
		LOG_DEBUG("Expanded line: [%s]\n", expanded);
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

	LOG_DEBUG("Entering heredoc input loop for delimiter: '%s'\n", delim);
	while (1)
	{
		line = readline("> ");
		LOG_DEBUG("HEREDOC input line: [%s]\n", line ? line : "NULL");

		if (!line)
		{
			LOG_WARN("readline() returned NULL (EOF or Ctrl+D)\n");
			close(fd);
			exit(1);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			LOG_DEBUG("Delimiter matched: '%s' → Ending heredoc input.\n", delim);
			free(line);
			break ;
		}
		write_line_to_pipe(line, fd, q, sh);
		free(line);
	}
	close(fd);
	LOG_DEBUG("HEREDOC pipe write end closed.\n");
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
	LOG_DEBUG("Waiting for heredoc child process: pid=%d\n", pid);
	waitpid(pid, &status, 0);

	LOG_DEBUG("Child exit status: %d\n", status);
	LOG_DEBUG("WIFSIGNALED=%d, WTERMSIG=%d\n", WIFSIGNALED(status), WIFSIGNALED(status) ? WTERMSIG(status) : -1);
	LOG_DEBUG("WIFEXITED=%d, WEXITSTATUS=%d\n", WIFEXITED(status), WIFEXITED(status) ? WEXITSTATUS(status) : -1);

	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		LOG_WARN("HEREDOC interrupted by SIGINT\n");
		sh->exit_status = 130;
		g_exit_status = 130;
		redir->fd = -1;
	}
	else if (WIFEXITED(status))
	{
		redir->fd = dup(pipefd[0]);
		LOG_DEBUG("HEREDOC read end duplicated to fd=%d\n", redir->fd);
	}
	else
	{
		LOG_ERROR("HEREDOC child failed unexpectedly\n");
		redir->fd = -1;
	}
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

	LOG_DEBUG("Creating heredoc pipe for delimiter: '%s'\n", redir->delimiter);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		LOG_ERROR("Failed to create pipe for heredoc\n");
		return ;
	}
	LOG_DEBUG("Pipe created: read_fd=%d, write_fd=%d\n", pipefd[0], pipefd[1]);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		LOG_ERROR("Failed to fork for heredoc\n");
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	if (pid == 0)
	{
		LOG_DEBUG("HEREDOC child process started.\n");
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(pipefd[0]);
		fill_hd_pipe(pipefd[1], redir->delimiter, sh, redir->delim_quote);
	}
	else
	{
		LOG_DEBUG("HEREDOC parent process, child pid=%d\n", pid);
		close_pip_and_wait(pipefd, redir, sh, pid);
	}
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
		LOG_DEBUG("Processing command for heredoc: %s\n", cmd->cmd ? cmd->cmd : "(null)");
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				LOG_DEBUG("Found heredoc redirection → delimiter: '%s'\n", redir->delimiter);
				create_heredoc_pipe(redir, sh);
				LOG_DEBUG("After heredoc, redir->fd = %d\n", redir->fd);
				if (redir->fd == -1)
				{
					LOG_WARN("Heredoc creation failed or was interrupted, skipping remaining\n");
					return ;
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
