/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:29:25 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/05 15:16:12 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

#define BUF_SIZE 1024

pid_t	get_pid_from_status(void)
{
	FILE	*file;
	char	buffer[BUF_SIZE];
	pid_t	pid;

	pid = -1;
	file = fopen("/proc/self/status", "r");
	if (!file)
	{
		perror("Error al abrir /proc/self/status");
		return (-1);
	}
	while (fgets(buffer, sizeof(buffer), file))
	{
		if (ft_strstr(buffer, "Pid:"))
		{
			sscanf(buffer, "Pid:\t%d", &pid);
			break ;
		}
	}
	fclose(file);
	if (pid == -1)
		printf("No se encontró la línea 'Pid:' en el archivo.\n");
	return (pid);
}
/*
int main() {
	pid_t pid = get_pid_from_status();
	if (pid != -1) {
		printf("El PID de este proceso es: %d\n", pid);
	} else {
		printf("Error al obtener el PID.\n");
	}
	return 0;
}*/
