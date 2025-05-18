/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:01:28 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/17 13:22:17 by mmarinov         ###   ########.fr       */
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
    if (joined[0] != '\0')
    {
        add_arg_to_cmd(cmd, joined);
    }
	free(joined);
	*tokens = (*tokens)->next;
	return (true);
}

static bool	token_into_cmd(t_tkn **tokens, t_cmd **curr_cmd, t_cmd **cmd_list)
{
	start_new_cmd_if_needed(curr_cmd);
	if ((*tokens)->type == TOK_PIPE)
		return (handle_pipe(cmd_list, curr_cmd, tokens));
	if (is_redirect((*tokens)->type))
		return (handle_redirect_wrapper(*curr_cmd, tokens));
	return (handle_word(*curr_cmd, tokens));
}

t_cmd	*parse_tokens(t_tkn *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!token_into_cmd(&tokens, &current_cmd, &cmd_list))
		{
			free_cmd_list(current_cmd);
			free_cmd_list(cmd_list);
			return (NULL);
		}
	}
	if (current_cmd)
		add_cmd_to_list(&cmd_list, current_cmd);
	return (cmd_list);
}
