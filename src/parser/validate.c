/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:00:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/07 12:16:31 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This function validates the command syntax for syntax errors.
 * 
 * Valid command examples:
 * - "echo hello"               - Regular command with args
 * - "> outfile"                - Just a redirection without command
 * - "echo hello > outfile"     - Command with redirection
 * 
 * Invalid command examples:
 * - ""                         - Empty command
 * - "|"                        - Pipe with no command
 * - "echo |"                   - Command ends with pipe
 * - "| echo"                   - Command starts with pipe
 * - "echo || grep"             - Double pipe (treated as two empty commands)
 * - "\"\""                     - Empty quotes (invalid in this shell)
 */
static int	validate_command_syntax(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (!cmd->cmd && cmd->redirs)
		return (1);
	if (!cmd->cmd && !cmd->redirs)
		return (0);
	if (cmd->cmd && cmd->cmd[0] == '\0')
		return (0);
	return (1);
}

/*
 * This function validates that pipes are used correctly.
 * 
 * Valid pipe sequences:
 * - "echo hello | grep h"      - Command | Command
 * - "cat file | grep a | wc"   - Multiple piped commands
 * - "cat file | > outfile"     - Command | Redirection
 * 
 * Invalid pipe sequences:
 * - "|"                        - Standalone pipe
 * - "| echo"                   - Command starts with pipe
 * - "echo || grep"             - Empty command between pipes
 * - "echo | |"                 - Multiple consecutive pipes
 */
static int	validate_pipes(t_cmd *cmd_list)
{
	t_cmd	*curr;

	curr = cmd_list;
	while (curr && curr->next)
	{
		if (!validate_command_syntax(curr))
			return (0);
		curr = curr->next;
	}
	if (curr && !validate_command_syntax(curr))
		return (0);
	return (1);
}

/*
 * Main validation function that checks the entire command list
 * for syntax errors.
 * 
 * Handles cases like:
 * - Empty command list
 * - Single commands
 * - Piped commands
 * - Commands with redirections
 * 
 * Returns 1 if valid, 0 if invalid (and prints error message)
 */
int	validate_syntax(t_cmd *cmd_list)
{
	if (!cmd_list)
		return (1);
	if (!validate_pipes(cmd_list))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (1);
}
