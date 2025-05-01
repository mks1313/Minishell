/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:12:10 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/21 15:09:11 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;
	char	*line;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			write(1, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
				break ;
			ft_putstr_fd(line, fd[1]);
			free(line);
		}
		free(line);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}
