/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tkn_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:00:00 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/13 13:12:21 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_name(t_tkn_type type)
{
	if (type == TOK_PIPE)
		return ("`|'");
	if (type == TOK_REDIR_IN)
		return ("`<'");
	if (type == TOK_REDIR_OUT)
		return ("`>'");
	if (type == TOK_APPEND)
		return ("`>>'");
	if (type == TOK_HEREDOC)
		return ("`<<'");
	return ("`newline'");
}

static void	print_syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd((char *)token, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

bool	validate_token_syntax(t_tkn *tokens)
{
	t_tkn		*prev;
	const char	*err_token;

	prev = NULL;
	if (!tokens)
		return (true);
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
		{
			if (!prev || !tokens->next || tokens->next->type == TOK_PIPE)
			{
				print_syntax_error("`|'");
				return (false);
			}
		}
		else if (tokens->type >= TOK_REDIR_IN && tokens->type <= TOK_HEREDOC)
		{
			if (!tokens->next)
			{
				print_syntax_error("`newline'");
				return (false);
			}
			if (tokens->next->type >= TOK_REDIR_IN && tokens->next->type <= TOK_HEREDOC)
			{
				err_token = get_token_name(tokens->next->type);
				print_syntax_error(err_token);
				return (false);
			}
			if (tokens->next->type == TOK_PIPE)
			{
				print_syntax_error("`|'");
				return (false);
			}
		}
		else if (tokens->type == TOK_OPERATOR)
		{
			print_syntax_error("`invalid operator'");
			return (false);
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (true);
}
