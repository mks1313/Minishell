/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:46:35 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 14:12:05 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Saves current stdin and stdout file descriptors into shell struct
 * so they can be restored later after redirections or execution.
 */
static void	backup_stdio(t_shell *shell)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
}

/**
 * Tokenizes and parses the input line.
 * Returns NULL on failure and sets shell->exit_status to 2.
 */
static t_cmd	*prepare_and_parse(char *line, t_shell *shell, t_tkn **tokens)
{
	*tokens = prepare_tokens(line, shell);
	if (!*tokens)
	{
		shell->exit_status = 2;
		return (NULL);
	}
	return (check_and_parse(*tokens, shell));
}

/**
 * Restores stdin and stdout, frees tokens and command list.
 * Also resets shell pointers to NULL to prevent dangling access.
 */
static void	cleanup_shell_state(t_shell *shell)
{
	restore_stdio(shell->stdin_backup, shell->stdout_backup);
	ft_free_tokens(shell->tkns);
	free_cmd_list(shell->cmds);
	shell->tkns = NULL;
	shell->cmds = NULL;
}

/**
 * Entry point to process a full command line:
 * tokenizes, parses, executes and then restores state.
 */
void	handle_commands(char *line, t_shell *shell)
{
	t_tkn	*tokens;
	t_cmd	*cmds;

	if (!shell || !line)
		return ;
	backup_stdio(shell);
	cmds = prepare_and_parse(line, shell, &tokens);
	if (!cmds)
		return ;
	shell->tkns = tokens;
	shell->cmds = cmds;
	handle_heredoc(cmds, shell);
	execute_commands(cmds, shell, line);
	cleanup_shell_state(shell);
}
