/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:29:25 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/24 16:35:12 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

pid_t	ft_get_pid(void)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	char	*pid_line;
	pid_t	pid;

	pid = -1;
	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (perror("Error at open  /proc/self/status"), -1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
	{
		perror("Error of read /proc/self/status");
		close(fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	pid_line = ft_strstr(buffer, "Pid:");
	if (pid_line)
		pid = ft_atoi(pid_line + 4);
	close(fd);
	return (pid);
}
