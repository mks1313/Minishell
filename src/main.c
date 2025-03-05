/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/03/05 18:36:10 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
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
	int		last_exit_status;
	t_data	*data;

	data = initialize_data();
	if (!data)
		return;
	last_exit_status = 0;
	cmd = ft_split(line, ' ');
	if (!cmd)
		return ;
	if (ft_strcmp(line, "exit") == 0)
	{
		free(line);
		ft_exit(NULL); // Asegúro de que ft_exit maneje la salida correctamente
	}
	else if (ft_strcmp(line, "env") == 0)
	{
		t_env *env_list = convert_env(envp);
		ft_env(env_list);
	}
	else if (ft_strcmp(line, "cd") == 0)
		ft_cd(cmd, data);
	else if (ft_strcmp(line, "echo") == 0)
		ft_echo(cmd);
	else
	{
		expand_variable(line, envp, last_exit_status);
		handle_double_quotes(line, envp);
		handle_single_quotes(line);
		last_exit_status = (last_exit_status + 1) % 256;
	}
	ft_free_split(cmd);
	free(data);
}

int	main(int argc, char *argv[], char *envp[])
{
	char				*line;
	struct sigaction	sa;
	int					last_exit_status;

	(void)argc;
	(void)argv;
	last_exit_status = 0;
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
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
		if (*line)
		{
			add_history(line);
			process_input(line, envp);
			handle_commands(line, envp);
			last_exit_status = (last_exit_status + 1) % 256;
		}
		free(line);
	}
	return (0);
}
