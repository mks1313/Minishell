/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:50 by mmarinov          #+#    #+#             */
/*   Updated: 2025/04/10 21:12:37 by mmarinov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	char	**new_args;

	i = 0;
	if (!cmd || !arg)
		return ;
	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		cmd->args[0] = ft_strdup(arg);
		cmd->args[1] = NULL;
		cmd->cmd = cmd->args[0];
		return ;
	}
	while (cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

static bool	is_redirect(t_tkn_type type)
{
	return (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_APPEND || type == TOK_HEREDOC);
}

static void	handle_redirect(t_redir **redir_list, t_tkn **tkn)
{
	t_redir	*redir;
	t_redir	*tmp;

	if (!*tkn || !(*tkn)->next)
		return ;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	if ((*tkn)->type == TOK_REDIR_IN)
		redir->type = REDIR_IN;
	else if ((*tkn)->type == TOK_REDIR_OUT)
		redir->type = REDIR_OUT;
	else if ((*tkn)->type == TOK_APPEND)
		redir->type = REDIR_APPEND;
	else if ((*tkn)->type == TOK_HEREDOC)
		redir->type = REDIR_HEREDOC;
	redir->file = ft_strdup((*tkn)->next->value);
	redir->fd = -1;
	redir->next = NULL;
	// Add to redirection list
	if (!*redir_list)
		*redir_list = redir;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	*tkn = (*tkn)->next;
}

static void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

t_cmd	*parse_tokens(t_tkn *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens)
	{
		if (!current_cmd)
			current_cmd = create_cmd();
		if (is_redirect(tokens->type))
			handle_redirect(&current_cmd->redirects, &tokens);
		else if (tokens->type == TOK_PIPE)
		{
			add_cmd_to_list(&cmd_list, current_cmd);
			current_cmd = NULL;
			tokens = tokens->next;
		}
		else
		{
			add_arg_to_cmd(current_cmd, tokens->value);
			tokens = tokens->next;
		}
	}
	if (current_cmd)
		add_cmd_to_list(&cmd_list, current_cmd);
	return (cmd_list);
}
