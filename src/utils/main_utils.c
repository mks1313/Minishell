/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:14:15 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 20:35:06 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function prepares the tokens from the input line by tokenizing it.
 * After tokenization, it validates the syntax of the tokens.
 * If the tokenization or syntax validation fails, it frees the memory
 * used by the tokens and returns NULL. If successful, it also expands any
 * environment variables within the tokens and returns the list of tokens.
 */
t_tkn	*prepare_tokens(char *line, t_shell *shell)
{
	t_tkn	*tokens;

	tokens = tokenize_input(line, shell);
	if (!tokens)
		return (NULL);
	if (!validate_token_syntax(tokens, shell))
	{
		ft_free_tokens(tokens);
		shell->tkns = NULL;
		return (NULL);
	}
	shell->tkns = tokens;
	expand_variable(shell);
	return (tokens);
}

/**
 * This function checks and parses the tokens to create executable commands.
 * It parses the tokens into a list of commands.
 * If token parsing or syntax validation fails, it frees the tokens and
 * the command list, then returns NULL. If everything is valid, it returns
 * the list of commands ready for execution.
 */
t_cmd	*check_and_parse(t_tkn *tokens, t_shell *shell)
{
	t_cmd	*cmds;

	cmds = parse_tokens(tokens, shell);
	if (!cmds)
	{
		ft_free_tokens(tokens);
		shell->tkns = NULL;
		return (NULL);
	}
	if (!validate_syntax(cmds, shell))
	{
		ft_free_tokens(tokens);
		free_cmd_list(cmds);
		shell->tkns = NULL;
		return (NULL);
	}
	return (cmds);
}

/**
 * This function restores the standard input and output descriptors after
 * a redirection has been performed. It ensures that the shell can resume
 * reading from and writing to the original file descriptors.
 */
void	restore_stdio(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
