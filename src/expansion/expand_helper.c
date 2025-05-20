/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:39:58 by mmarinov          #+#    #+#             */
/*   Updated: 2025/05/20 17:36:53 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	return (ft_calloc(1, sizeof(t_cmd)));
}

char	*join_token_parts(t_tkn_part *parts)
{
	char	*tmp;
	char	*result;
	char	*joined;

	result = ft_strdup("");
	while (parts)
	{
		tmp = ft_strdup(parts->value);
		joined = ft_strjoin(result, tmp);
		free(result);
		free(tmp);
		result = joined;
		parts = parts->next;
	}
	return (result);
}

bool	handl_pipe(t_cmd **cmd_lst, t_cmd **cur_cmd, t_tkn **tkns, t_shell *sh)
{
	if (!*cur_cmd || (!(*cur_cmd)->cmd && !(*cur_cmd)->redirs))
		return (syntax_error(sh, SYN_ERR_PIPE, 0));
	add_cmd_to_list(cmd_lst, *cur_cmd);
	*cur_cmd = NULL;
	*tkns = (*tkns)->next;
	return (true);
}

bool	handle_redirect_wrapper(t_cmd *cmd, t_tkn **tokens, t_shell *shell)
{
	t_redir	*redir;

	if (!(*tokens)->next)
		return (syntax_error(shell, SYN_ERR_NL, 0));
	redir = create_redir(*tokens);
	if (!redir)
		return (false);
	add_redir_to_list(&cmd->redirs, redir);
	*tokens = (*tokens)->next;
	*tokens = (*tokens)->next;
	return (true);
}

char	*handle_env_variable(char *value, int *i, t_env *env)
{
	int		start;
	char	*key;
	char	*val;

	start = *i;
	while (ft_isalnum(value[*i]) || value[*i] == '_')
		(*i)++;
	key = ft_substr(value, start, *i - start);
	val = ft_getenv(key, env);
	free(key);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}
