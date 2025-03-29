/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:12:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/03/29 13:06:35 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * clean_array - Libera toda la memoria de un array de strings terminado en NULL
 * @array: El array a liberar
 *
 * Esta función libera cada string en el array y luego el propio array.
 * Es segura para usar con NULL.
 */
void	clean_array(char **array)
{
    int	i;

    if (!array)
        return ;
    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

static char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = ft_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin3(paths[i], "/", cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			clean_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	clean_array(paths);
	return (NULL);
}

char	**env_to_array(t_env *env)
{
	int	i;
	int	count;
	char	**env_array;
	t_env	*curr;

	count = 0;
	curr = env;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	curr = env;
	while (curr)
	{
		env_array[i] = ft_strjoin3(curr->key, "=", curr->value);
		i++;
		curr = curr->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	execute_external_command(char *cmd, char **args, t_env *env)
{
	char	*cmd_path;
	char	**envp;
	int	status;
	pid_t	pid;

	cmd_path = find_command_path(cmd, env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		envp = env_to_array(env);
		execve(cmd_path, args, envp);
		clean_array(envp);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
}
