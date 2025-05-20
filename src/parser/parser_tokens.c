/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:01:28 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 11:45:10 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_tkn_type type)
{
	return (type >= TOK_REDIR_IN && type <= TOK_HEREDOC);
}

static void	start_new_cmd_if_needed(t_cmd **current_cmd)
{
	if (!*current_cmd)
		*current_cmd = create_cmd();
}

static bool	handle_word(t_cmd *cmd, t_tkn **tokens)
{
	char	*joined;

	joined = join_token_parts((*tokens)->parts);
	if (joined[0] == '\0' && cmd->args == NULL && cmd->redirs == NULL)
	{
		free(joined);
		*tokens = (*tokens)->next;
		return (true);
	}
	add_arg_to_cmd(cmd, joined);
	free(joined);
	*tokens = (*tokens)->next;
	return (true);
}

static bool	tkn_t_cmd(t_tkn **tkns, t_cmd **c_cmd, t_cmd **cmd_lst, t_shell *sh)
{
	start_new_cmd_if_needed(c_cmd);
	if ((*tkns)->type == TOK_PIPE)
		return (handl_pipe(cmd_lst, c_cmd, tkns, sh));
	if (is_redirect((*tkns)->type))
		return (handle_redirect_wrapper(*c_cmd, tkns, sh));
	return (handle_word(*c_cmd, tkns));
}

t_cmd	*parse_tokens(t_tkn *tokens, t_shell *shell)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!tkn_t_cmd(&tokens, &current_cmd, &cmd_list, shell))
		{
			shell->exit_status = 2;
			free_cmd_list(current_cmd);
			free_cmd_list(cmd_list);
			return (NULL);
		}
	}
	if (current_cmd && (current_cmd->cmd || current_cmd->redirs))
		add_cmd_to_list(&cmd_list, current_cmd);
	else
		free_cmd_list(current_cmd);
	return (cmd_list);
}
