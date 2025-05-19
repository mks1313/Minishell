/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:14:15 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/19 14:49:32 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_tkn	*prepare_tokens(char *line, t_shell *shell)
{
	t_tkn	*tokens;

	tokens = tokenize_input(line);
	if (!tokens)
		return (NULL);
	if (!validate_token_syntax(tokens, shell))
	{
		shell->exit_status = 2;
		ft_free_tokens(tokens);
		shell->tkns = NULL;
		return (NULL);
	}
	shell->tkns = tokens;
	expand_variable(shell);
	return (tokens);
}

static t_cmd	*check_and_parse(t_tkn *tokens, t_shell *shell)
{
	t_cmd	*cmds;

	cmds = parse_tokens(tokens, shell);
	if (!cmds)
	{
		ft_free_tokens(tokens);
		shell->tkns = NULL;
		return (NULL);
	}
	if (!validate_syntax(cmds))
	{
		shell->exit_status = 2;
		ft_free_tokens(tokens);
		free_cmd_list(cmds);
		shell->tkns = NULL;
		return (NULL);
	}
	return (cmds);
}

static void	restore_stdio(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	handle_commands(char *line, t_shell *shell)
{
	t_tkn	*tokens;
	t_cmd	*cmds;
	int		stdin_backup;
	int		stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (!shell || !line)
		return ;
	tokens = prepare_tokens(line, shell);
	if (!tokens)
		return ;
	cmds = check_and_parse(tokens, shell);
	if (!cmds)
		return ;
	shell->cmds = cmds;
	handle_heredoc(cmds, shell);
	execute_commands(cmds, shell, line);
	restore_stdio(stdin_backup, stdout_backup);
	ft_free_tokens(tokens);
	free_cmd_list(cmds);
	shell->tkns = NULL;
	shell->cmds = NULL;
}
