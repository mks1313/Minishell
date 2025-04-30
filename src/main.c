/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:39:49 by meghribe          #+#    #+#             */
/*   Updated: 2025/04/30 19:06:44 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin_command(char *cmd)
{
	const char	*builtins[] = {"exit", "env", "cd", "echo",
		"pwd", "export", "unset", NULL};
	int			i;

	if (!cmd)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void execute_simple_pipe(t_cmd *cmd1, t_cmd *cmd2, t_shell *shell)
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
        return perror("pipe");

    pid1 = fork();
    if (pid1 == -1)
        return perror("fork");

    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        if (is_builtin_command(cmd1->cmd))
            handle_builtin_commands(cmd1, shell, NULL);
        else
            execute_single_command(cmd1, shell->env);
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == -1)
        return perror("fork");

    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        if (is_builtin_command(cmd2->cmd))
            handle_builtin_commands(cmd2, shell, NULL);
        else
            execute_single_command(cmd2, shell->env);
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}


void	execute_commands(t_cmd *cmd, t_shell *shell, char *line)
{
	int		n_cmds;
	//t_pipe	pipe_data;

	if (!cmd || !cmd->cmd || !shell || !line)
		return ;
	n_cmds = count_cmds(cmd);
	if (n_cmds == 1)
	{
		if (is_builtin_command(cmd->cmd))
			handle_builtin_commands(cmd, shell, line);
		else
			execute_single_command(cmd, shell->env);
	}
	if (cmd && cmd->next && !cmd->next->next)
	{
		//pipe_data.n_cmds = n_cmds;
		//execute_piped_commands(cmd, &pipe_data, shell->env);
		//char *cmd1[] = {"ls", NULL};
		//char *cmd2[] = {"wc", NULL};
		//execute_pipe(cmd, cmd->next);
		execute_simple_pipe(cmd, cmd->next, shell);
	}
}

/*
static void debug(t_tkn *tkn)
{
	t_tkn *curr = tkn;
	while (curr)
	{
		printf("Token: %s | type: %d | sq: %d | dq: %d\n",
				curr->value, curr->type, curr->single_quote, curr->double_quote);
		curr = curr->next;
	}
}*/

static void	handle_commands(char *line, t_shell *shell)
{
	t_tkn	*tokens;
	t_cmd	*cmds;

	if (!shell || !line)
		return ;
	tokens = tokenize_input(line);
	if (!tokens)
		return ;
	lex_tokens(tokens);
	shell->tkns = tokens;
	expand_variable(shell);
	cmds = parse_tokens(tokens);
	if (!cmds)
	{
		ft_free_tokens(tokens);
		shell->tkns = NULL;
		return ;
	}
	shell->cmds = cmds;
	execute_commands(cmds, shell, line);
	ft_free_tokens(tokens);
	shell->tkns = NULL;
	ft_free_list(cmds);
	shell->cmds = NULL;
}

static int	process_input_line(char **line_ptr, t_shell *shell)
{
	char	*line;

	line = readline(GREEN"minishell$ "RES);
	*line_ptr = line;
	if (!line)
		return (ft_putstr_fd("\nexit\n", 1), SHELL_EXIT);
	if (*line)
	{
		add_history(line);
		handle_commands(line, shell);
	}
	return (SHELL_CONTINUE);
}

static int	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (process_input_line(&line, shell) == SHELL_EXIT)
			return (EXIT_SUCCESS);
		free(line);
	}
	return (EXIT_SUCCESS);
}

static int	clean_exit(t_shell *shell, int status)
{
	free_data(shell);
	rl_clear_history();
	return (status);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	if (init_shell(&shell))
		return (EXIT_FAILURE);
	if (setup_environment(shell, envp))
		return (clean_exit(shell, EXIT_FAILURE));
	return (clean_exit(shell, shell_loop(shell)));
}
