/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:29:39 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/12 17:09:06 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*quote_type_str(t_tkn_quote q)
{
	if (q == Q_NONE)
		return ("Q_NONE");
	if (q == Q_SINGLE)
		return ("Q_SINGLE");
	if (q == Q_DOUBLE)
		return ("Q_DOUBLE");
	if (q == Q_MIX)
		return ("Q_MIX");
	return ("UNKNOWN");
}

const char	*token_type_str(t_tkn_type t)
{
	if (t == TOK_WORD)
		return ("WORD");
	if (t == TOK_PIPE)
		return ("PIPE");
	if (t == TOK_REDIR_IN)
		return ("REDIR_IN");
	if (t == TOK_REDIR_OUT)
		return ("REDIR_OUT");
	if (t == TOK_APPEND)
		return ("APPEND");
	if (t == TOK_HEREDOC)
		return ("HEREDOC");
	if (t == TOK_OPERATOR)
		return ("OPERATOR");
	return ("UNKNOWN");
}

void	for_tokens(t_tkn *tokens)
{
	int			i;
	int			j;
	t_tkn_part	*part;

	i = 0;
	dprintf(STDERR_FILENO, "========== TOKENS ==========""\n");
	while (tokens)
	{
		dprintf(STDERR_FILENO, "Token #%d → type: %s\n", i++, token_type_str(tokens->type));
		part = tokens->parts;
		j = 0;
		while (part)
		{
			dprintf(STDERR_FILENO, "  Part #%d: [%s] | quote: %s\n",
				j++, part->value ? part->value : "(null)", quote_type_str(part->quote));
			part = part->next;
		}
		tokens = tokens->next;
	}
	dprintf(STDERR_FILENO, "============================\n");
}

void	por_cmds(t_cmd *cmds)
{
	int i = 0;
	while (cmds)
	{
		dprintf(STDERR_FILENO, "========== CMD #%d ==========""\n", i++);
		dprintf(STDERR_FILENO, "Command   : %s\n", cmds->cmd ? cmds->cmd : "(null)");
		dprintf(STDERR_FILENO, "Args      : ");
		if (cmds->args)
		{
			for (int j = 0; cmds->args[j]; j++)
				dprintf(STDERR_FILENO, "[%s] ", cmds->args[j]);
		}
		else
			dprintf(STDERR_FILENO, "(null)");
		dprintf(STDERR_FILENO, "\n");

		t_redir *r = cmds->redirs;
		while (r)
		{
			const char *type =
				r->type == REDIR_IN ? "<" :
				r->type == REDIR_OUT ? ">" :
				r->type == REDIR_APPEND ? ">>" :
				r->type == REDIR_HEREDOC ? "<<" : "?";

			dprintf(STDERR_FILENO, "Redir     : %s ", type);
			if (r->file)
				dprintf(STDERR_FILENO, "file: %s", r->file);
			if (r->delimiter)
				dprintf(STDERR_FILENO, " delimiter: %s", r->delimiter);
			dprintf(STDERR_FILENO, "\n");
			r = r->next;
		}
		cmds = cmds->next;
	}
	dprintf(STDERR_FILENO, "============================\n");
}
