/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/03 22:42:21 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	handle_commands(char *line, char **envp)
{
	char	**cmd;

	cmd = ft_split(line, ' ');
	if (!cmd)
		return;
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		ft_exit(NULL); // Asegúrate de que ft_exit maneje la salida correctamente
	}
	else if (ft_strcmp(line, "env") == 0)
		ft_env(envp);
	else if (ft_strcmp(line, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(line, "echo") == 0)
		ft_echo(cmd);
	else
	{
		expand_variable(line, envp);
		handle_double_quotes(line, envp);
		handle_single_quotes(line, envp);
	}
	ft_free_split(cmd);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	struct sigaction sa;

	(void)argc;
	(void)argv;

	set_sig(&sa, handle_signal);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 2);
			clear_history();
			ft_exit(NULL);
		}
		if (*line)  // Si la línea no está vacía
		{
			add_history(line);
			handle_commands(line, envp);
		}
		free(line);
	}
	return (0);
}
