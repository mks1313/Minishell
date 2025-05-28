/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:14:15 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/28 14:02:37 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	restore_stdio(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
